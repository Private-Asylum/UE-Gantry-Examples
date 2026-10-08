// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Player/Local/GTLocalPlayer.h"

#include "GantryExamplesLogCategories.h"

UGTLocalPlayer::UGTLocalPlayer()
{
}

void UGTLocalPlayer::PlayerAdded(UGameViewportClient* InViewportClient, FPlatformUserId InUserId)
{
	Super::PlayerAdded(InViewportClient, InUserId);

	UE_LOG(LogGTPlayer, Log, TEXT("Local player added. Platform user: %d"), InUserId.GetInternalId());
}

void UGTLocalPlayer::PlayerRemoved()
{
	UE_LOG(LogGTPlayer, Log, TEXT("Local player removed."));

	Super::PlayerRemoved();
}

bool UGTLocalPlayer::SpawnPlayActor(const FString& URL, FString& OutError, UWorld* InWorld)
{
	return Super::SpawnPlayActor(URL, OutError, InWorld);
}

void UGTLocalPlayer::ReceivedPlayerController(APlayerController* NewController)
{
	Super::ReceivedPlayerController(NewController);

	OnPlayerControllerChanged.Broadcast(this, NewController);
}

void UGTLocalPlayer::SetControllerId(int32 NewControllerId)
{
	Super::SetControllerId(NewControllerId);
}
