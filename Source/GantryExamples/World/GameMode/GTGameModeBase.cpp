// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/GameMode/GTGameModeBase.h"

#include "GantryExamplesLogCategories.h"
#include "Pawn/Character/GTCharacter.h"
#include "Player/Camera/GTPlayerCameraManager.h"
#include "Player/Controller/GTPlayerController.h"
#include "Player/State/GTPlayerState.h"
#include "UI/GTHUD.h"
#include "World/GameMode/GTGameSession.h"
#include "World/GameState/GTGameStateBase.h"

AGTGameModeBase::AGTGameModeBase()
{
	// Point every framework slot at the project class. Blueprint subclasses can still override
	// any of these; this only sets the floor.
	GameStateClass = AGTGameStateBase::StaticClass();
	PlayerControllerClass = AGTPlayerController::StaticClass();
	PlayerStateClass = AGTPlayerState::StaticClass();
	DefaultPawnClass = AGTCharacter::StaticClass();
	HUDClass = AGTHUD::StaticClass();
	GameSessionClass = AGTGameSession::StaticClass();
}

void AGTGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogGTWorld, Log, TEXT("InitGame. Map: %s Options: %s"), *MapName, *Options);
}

void AGTGameModeBase::InitGameState()
{
	Super::InitGameState();
}

void AGTGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogGTWorld, Log, TEXT("Player logged in: %s"),
		NewPlayer && NewPlayer->PlayerState ? *NewPlayer->PlayerState->GetPlayerName() : TEXT("<unknown>"));
}

void AGTGameModeBase::Logout(AController* Exiting)
{
	UE_LOG(LogGTWorld, Log, TEXT("Controller logging out: %s"), *GetNameSafe(Exiting));

	Super::Logout(Exiting);
}

void AGTGameModeBase::GenericPlayerInitialization(AController* C)
{
	Super::GenericPlayerInitialization(C);

	// At this point the player state exists and the controller is ready for gameplay setup.
	K2_OnPlayerFullyInitialised(C);
}

AActor* AGTGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}

UClass* AGTGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
