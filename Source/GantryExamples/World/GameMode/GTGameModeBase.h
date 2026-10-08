// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"

#include "GTGameModeBase.generated.h"

/**
 * Lightweight game mode with no match state machine.
 *
 * Use this for front end maps, cinematics, tools maps and anything else that needs the class
 * defaults (pawn, controller, HUD, player state) without the waiting-to-start / in-progress /
 * post-match flow. For actual gameplay use AGTGameMode.
 *
 * Remember the game mode only exists on the server (and in standalone). Anything a client needs
 * to know belongs on AGTGameStateBase.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGTGameModeBase();

	/* AGameModeBase interface. */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void GenericPlayerInitialization(AController* C) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	/* AGameModeBase interface. */

protected:

	/**
	 * Called once a controller is fully initialised: player state replicated, pawn possessed.
	 * Prefer this over PostLogin for gameplay work, since PostLogin fires before the pawn exists.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "GantryExamples|Game Mode", meta = (DisplayName = "On Player Fully Initialised"))
	void K2_OnPlayerFullyInitialised(AController* Controller);
};
