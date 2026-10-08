// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/GameMode/GTGameMode.h"

#include "GantryExamplesLogCategories.h"
#include "Pawn/Character/GTCharacter.h"
#include "Player/Controller/GTPlayerController.h"
#include "Player/State/GTPlayerState.h"
#include "UI/GTHUD.h"
#include "World/GameMode/GTGameSession.h"
#include "World/GameState/GTGameState.h"

#include "Engine/World.h"

AGTGameMode::AGTGameMode()
	: MinimumPlayersToStart(1)
	, MatchDurationSeconds(0.0f)
	, MatchStartWorldTime(-1.0f)
{
	GameStateClass = AGTGameState::StaticClass();
	PlayerControllerClass = AGTPlayerController::StaticClass();
	PlayerStateClass = AGTPlayerState::StaticClass();
	DefaultPawnClass = AGTCharacter::StaticClass();
	HUDClass = AGTHUD::StaticClass();
	GameSessionClass = AGTGameSession::StaticClass();

	// Start in WaitingToStart and let ReadyToStartMatch decide, rather than dropping straight
	// into gameplay before players have connected.
	bDelayedStart = true;
}

void AGTGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogGTWorld, Log, TEXT("InitGame. Map: %s Options: %s"), *MapName, *Options);
}

void AGTGameMode::GenericPlayerInitialization(AController* C)
{
	Super::GenericPlayerInitialization(C);

	UE_LOG(LogGTWorld, Verbose, TEXT("Controller fully initialised: %s"), *GetNameSafe(C));
}

AActor* AGTGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}

EGTMatchPhase AGTGameMode::GetMatchPhase() const
{
	return GTWorld::MatchStateToPhase(GetMatchState());
}

void AGTGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	UE_LOG(LogGTWorld, Log, TEXT("Match waiting to start."));
}

bool AGTGameMode::ReadyToStartMatch_Implementation()
{
	if (!bDelayedStart)
	{
		return Super::ReadyToStartMatch_Implementation();
	}

	return GetMatchState() == MatchState::WaitingToStart && NumPlayers >= MinimumPlayersToStart;
}

void AGTGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	MatchStartWorldTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	UE_LOG(LogGTWorld, Log, TEXT("Match started with %d player(s)."), NumPlayers);
}

bool AGTGameMode::ReadyToEndMatch_Implementation()
{
	if (MatchDurationSeconds <= 0.0f || MatchStartWorldTime < 0.0f || !GetWorld())
	{
		return Super::ReadyToEndMatch_Implementation();
	}

	return (GetWorld()->GetTimeSeconds() - MatchStartWorldTime) >= MatchDurationSeconds;
}

void AGTGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	MatchStartWorldTime = -1.0f;

	UE_LOG(LogGTWorld, Log, TEXT("Match ended."));
}

void AGTGameMode::HandleMatchAborted()
{
	Super::HandleMatchAborted();

	MatchStartWorldTime = -1.0f;

	UE_LOG(LogGTWorld, Warning, TEXT("Match aborted."));
}

void AGTGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	UE_LOG(LogGTWorld, Verbose, TEXT("Match state set to %s."), *GetMatchState().ToString());
}
