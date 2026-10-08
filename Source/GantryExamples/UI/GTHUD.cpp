// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "UI/GTHUD.h"

#include "Core/Settings/GTDeveloperSettings.h"
#include "Core/Tags/GTGameplayTags.h"
#include "GantryExamplesLogCategories.h"

#include "Blueprint/UserWidget.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "GameFramework/PlayerController.h"

AGTHUD::AGTHUD()
	: bDrawDebugOverlay(false)
{
	PrimaryActorTick.bCanEverTick = false;

	// Sensible defaults so a subclass that configures nothing still works.
	HUDLayers.Add({ GTGameplayTags::UI_Layer_Game.GetTag(),  0,   EGTUIInputPolicy::GameOnly });
	HUDLayers.Add({ GTGameplayTags::UI_Layer_Menu.GetTag(),  100, EGTUIInputPolicy::MenuOnly });
	HUDLayers.Add({ GTGameplayTags::UI_Layer_Modal.GetTag(), 200, EGTUIInputPolicy::MenuOnly });
	HUDLayers.Add({ GTGameplayTags::UI_Layer_Debug.GetTag(), 300, EGTUIInputPolicy::GameOnly });
}

void AGTHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGTHUD::BeginPlay()
{
	Super::BeginPlay();

	if (const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get())
	{
		bDrawDebugOverlay = Settings->bShowDebugHUDByDefault && Settings->AllowsCheats();
	}
}

void AGTHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (UUserWidget* Widget : ActiveWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}

	ActiveWidgets.Empty();
	WidgetLayerTags.Empty();

	Super::EndPlay(EndPlayReason);
}

void AGTHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bDrawDebugOverlay)
	{
		DrawDebugOverlay();
	}
}

void AGTHUD::ShowHUD()
{
	Super::ShowHUD();
}

void AGTHUD::DrawDebugOverlay()
{
	if (!Canvas)
	{
		return;
	}

	const FString Text = FString::Printf(TEXT("GantryExamples debug overlay | Widgets: %d"), ActiveWidgets.Num());

	FCanvasTextItem TextItem(FVector2D(16.0f, 16.0f), FText::FromString(Text), UEngine::GetSmallFont(), FLinearColor::White);
	TextItem.EnableShadow(FLinearColor::Black);

	Canvas->DrawItem(TextItem);
}

const FGTHUDLayer* AGTHUD::FindLayer(const FGameplayTag& LayerTag) const
{
	return HUDLayers.FindByPredicate([&LayerTag](const FGTHUDLayer& Layer) { return Layer.LayerTag == LayerTag; });
}

UUserWidget* AGTHUD::PushWidgetToLayer(TSubclassOf<UUserWidget> WidgetClass, FGameplayTag LayerTag)
{
	APlayerController* OwningPC = GetOwningPlayerController();

	if (!WidgetClass || !OwningPC)
	{
		return nullptr;
	}

	const FGTHUDLayer* Layer = FindLayer(LayerTag);

	if (!Layer)
	{
		UE_LOG(LogGTUI, Warning, TEXT("No HUD layer configured for tag %s on %s."), *LayerTag.ToString(), *GetName());
		return nullptr;
	}

	UUserWidget* Widget = CreateWidget<UUserWidget>(OwningPC, WidgetClass);

	if (!Widget)
	{
		return nullptr;
	}

	Widget->AddToPlayerScreen(Layer->ZOrder);
	ActiveWidgets.Add(Widget);
	WidgetLayerTags.Add(Widget, LayerTag);

	switch (Layer->InputPolicy)
	{
	case EGTUIInputPolicy::MenuOnly:
		OwningPC->SetInputMode(FInputModeUIOnly());
		OwningPC->SetShowMouseCursor(true);
		break;

	case EGTUIInputPolicy::GameAndMenu:
		OwningPC->SetInputMode(FInputModeGameAndUI());
		OwningPC->SetShowMouseCursor(true);
		break;

	case EGTUIInputPolicy::GameOnly:
	default:
		break;
	}

	return Widget;
}

void AGTHUD::PopWidget(UUserWidget* Widget)
{
	if (!Widget)
	{
		return;
	}

	Widget->RemoveFromParent();
	ActiveWidgets.Remove(Widget);
	WidgetLayerTags.Remove(Widget);

	// Hand input back to gameplay once nothing is left that wanted it.
	if (ActiveWidgets.IsEmpty())
	{
		if (APlayerController* OwningPC = GetOwningPlayerController())
		{
			OwningPC->SetInputMode(FInputModeGameOnly());
			OwningPC->SetShowMouseCursor(false);
		}
	}
}

void AGTHUD::ClearLayer(FGameplayTag LayerTag)
{
	for (int32 Index = ActiveWidgets.Num() - 1; Index >= 0; --Index)
	{
		UUserWidget* Widget = ActiveWidgets[Index];
		const FGameplayTag* WidgetLayer = Widget ? WidgetLayerTags.Find(Widget) : nullptr;

		if (WidgetLayer && *WidgetLayer == LayerTag)
		{
			PopWidget(Widget);
		}
	}
}
