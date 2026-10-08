// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "UI/GTUI.h"

#include "GameFramework/HUD.h"

#include "GTHUD.generated.h"

class UGTUserWidget;
class UUserWidget;

/**
 * Per-player HUD actor, owned by the local player controller and never replicated.
 *
 * Two jobs. First, the canvas debug draw that AHUD has always done, which is still the cheapest
 * way to get numbers on screen. Second, owning the widget layer stack, so gameplay code pushes a
 * widget to a layer tag instead of guessing at z-orders.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTHUD : public AHUD
{
	GENERATED_BODY()

public:

	AGTHUD();

	/* AActor interface. */
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	/* AActor interface. */

	/* AHUD interface. */
	virtual void PostInitializeComponents() override;
	virtual void DrawHUD() override;
	virtual void ShowHUD() override;
	/* AHUD interface. */

	/** Creates a widget and adds it to the layer identified by LayerTag. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|UI", meta = (DeterminesOutputType = "WidgetClass"))
	UUserWidget* PushWidgetToLayer(TSubclassOf<UUserWidget> WidgetClass, FGameplayTag LayerTag);

	/** Removes a widget previously pushed with PushWidgetToLayer. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|UI")
	void PopWidget(UUserWidget* Widget);

	/** Removes every widget on a layer. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|UI")
	void ClearLayer(FGameplayTag LayerTag);

protected:

	/** Canvas debug draw. Only called when the debug layer is enabled. */
	virtual void DrawDebugOverlay();

	/** Finds the configured layer for a tag, or nullptr when the tag is not configured. */
	const FGTHUDLayer* FindLayer(const FGameplayTag& LayerTag) const;

	/** Layer definitions, ordered however you like; ZOrder decides what draws on top. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|UI", meta = (TitleProperty = "LayerTag"))
	TArray<FGTHUDLayer> HUDLayers;

	/** Widgets currently on screen, in push order. */
	UPROPERTY(Transient)
	TArray<TObjectPtr<UUserWidget>> ActiveWidgets;

	/** Which layer each active widget was pushed to. UUserWidget does not remember this itself. */
	UPROPERTY(Transient)
	TMap<TObjectPtr<UUserWidget>, FGameplayTag> WidgetLayerTags;

	/** Draws the canvas debug overlay. Toggled by the GT.DebugHUD console command. */
	UPROPERTY(Transient, BlueprintReadWrite, Category = "GantryExamples|UI")
	bool bDrawDebugOverlay;
};
