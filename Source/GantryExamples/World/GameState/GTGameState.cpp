// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/GameState/GTGameState.h"

#include "GantryExamplesLogCategories.h"

#include "Net/UnrealNetwork.h"

AGTGameState::AGTGameState()
	: MatchEndServerTime(-1.0f)
	, LastBroadcastPhase(EGTMatchPhase::Unknown)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AGTGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGTGameState, MatchEndServerTime);
}

float AGTGameState::GetMatchTimeRemaining() const
{
	if (MatchEndServerTime < 0.0f)
	{
		return -1.0f;
	}

	return FMath::Max(0.0f, MatchEndServerTime - static_cast<float>(GetServerWorldTimeSeconds()));
}

void AGTGameState::OnRep_MatchState()
{
	Super::OnRep_MatchState();

	BroadcastMatchPhase();
}

void AGTGameState::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	BroadcastMatchPhase();
}

void AGTGameState::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	BroadcastMatchPhase();
}

void AGTGameState::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	BroadcastMatchPhase();
}

void AGTGameState::BroadcastMatchPhase()
{
	const EGTMatchPhase Phase = GetMatchPhase();

	if (Phase == LastBroadcastPhase)
	{
		return;
	}

	LastBroadcastPhase = Phase;

	UE_LOG(LogGTWorld, Verbose, TEXT("Game state match phase is now %s."), *GetMatchState().ToString());

	OnMatchPhaseChanged.Broadcast(Phase);
	OnMatchPhaseChangedNative.Broadcast(Phase);
}
