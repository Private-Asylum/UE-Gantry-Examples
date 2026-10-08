// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/GameState/GTGameStateBase.h"

#include "GantryExamplesLogCategories.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

AGTGameStateBase::AGTGameStateBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AGTGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGTGameStateBase::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	UE_LOG(LogGTWorld, Verbose, TEXT("Game state begin play."));
}

void AGTGameStateBase::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	OnPlayerStateAdded.Broadcast(PlayerState);
}

void AGTGameStateBase::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	OnPlayerStateRemoved.Broadcast(PlayerState);
}

void AGTGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
