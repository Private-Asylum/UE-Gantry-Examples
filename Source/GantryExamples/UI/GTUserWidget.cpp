// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "UI/GTUserWidget.h"

#include "Player/Controller/GTPlayerController.h"
#include "UI/GTHUD.h"

void UGTUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UGTUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGTUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

AGTPlayerController* UGTUserWidget::GetGTPlayerController() const
{
	return Cast<AGTPlayerController>(GetOwningPlayer());
}

AGTHUD* UGTUserWidget::GetGTHUD() const
{
	const APlayerController* OwningPC = GetOwningPlayer();

	return OwningPC ? Cast<AGTHUD>(OwningPC->GetHUD()) : nullptr;
}
