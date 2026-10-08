// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Engine/GTGameViewportClient.h"

#include "GantryExamplesLogCategories.h"

void UGTGameViewportClient::Init(FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);

	UE_LOG(LogGTCore, Log, TEXT("GTGameViewportClient initialised."));
}

void UGTGameViewportClient::DetachViewportClient()
{
	Super::DetachViewportClient();
}

bool UGTGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	// Return true here to swallow an input before it reaches any player controller. Useful for
	// modal UI and for debug overlays that must win against gameplay bindings.
	return Super::InputKey(EventArgs);
}

void UGTGameViewportClient::ReceivedFocus(FViewport* InViewport)
{
	bHasWindowFocus = true;

	Super::ReceivedFocus(InViewport);
}

void UGTGameViewportClient::LostFocus(FViewport* InViewport)
{
	bHasWindowFocus = false;

	Super::LostFocus(InViewport);
}
