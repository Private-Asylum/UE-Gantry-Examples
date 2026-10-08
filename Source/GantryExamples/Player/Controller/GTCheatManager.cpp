// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Player/Controller/GTCheatManager.h"

#include "GantryExamplesLogCategories.h"
#include "World/GameMode/GTGameMode.h"
#include "World/GameState/GTGameState.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

UGTCheatManager::UGTCheatManager()
{
}

void UGTCheatManager::InitCheatManager()
{
	Super::InitCheatManager();

	UE_LOG(LogGTPlayer, Log, TEXT("GantryExamples cheat manager available. Try GTDumpPlayer."));
}

void UGTCheatManager::GTDumpPlayer()
{
	const APlayerController* PC = GetPlayerController();

	if (!PC)
	{
		return;
	}

	UE_LOG(LogGTPlayer, Display, TEXT("Controller: %s | PlayerState: %s | Pawn: %s"),
		*GetNameSafe(PC),
		PC->PlayerState ? *PC->PlayerState->GetPlayerName() : TEXT("<none>"),
		*GetNameSafe(PC->GetPawn()));
}

void UGTCheatManager::GTDumpMatch()
{
	const UWorld* World = GetWorld();

	if (!World)
	{
		return;
	}

	if (const AGTGameState* GameState = World->GetGameState<AGTGameState>())
	{
		UE_LOG(LogGTPlayer, Display, TEXT("Match state: %s | Players: %d | Time remaining: %.1f"),
			*GameState->GetMatchState().ToString(),
			GameState->PlayerArray.Num(),
			GameState->GetMatchTimeRemaining());
	}
	else
	{
		UE_LOG(LogGTPlayer, Display, TEXT("No GTGameState in this world."));
	}
}

void UGTCheatManager::GTStartMatch()
{
	UWorld* World = GetWorld();

	if (AGTGameMode* GameMode = World ? World->GetAuthGameMode<AGTGameMode>() : nullptr)
	{
		GameMode->StartMatch();
	}
	else
	{
		UE_LOG(LogGTPlayer, Warning, TEXT("GTStartMatch requires server authority and an GTGameMode."));
	}
}

void UGTCheatManager::GTEndMatch()
{
	UWorld* World = GetWorld();

	if (AGTGameMode* GameMode = World ? World->GetAuthGameMode<AGTGameMode>() : nullptr)
	{
		GameMode->EndMatch();
	}
	else
	{
		UE_LOG(LogGTPlayer, Warning, TEXT("GTEndMatch requires server authority and an GTGameMode."));
	}
}
