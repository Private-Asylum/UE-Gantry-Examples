// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/CheatManager.h"

#include "GTCheatManager.generated.h"

/**
 * Developer cheats and console commands, scoped to a player controller.
 *
 * Only created when cheats are allowed (see AGTPlayerController::AddCheats), which is driven by
 * the build environment in UGTDeveloperSettings. Every UFUNCTION(Exec) declared here becomes a
 * console command, so this is the cheapest place to add a debug affordance.
 */
UCLASS(Within = PlayerController)
class GANTRYEXAMPLES_API UGTCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	UGTCheatManager();

	/* UCheatManager interface. */
	virtual void InitCheatManager() override;
	/* UCheatManager interface. */

	/** Prints the owning player's controller, state and pawn to the log. */
	UFUNCTION(Exec)
	void GTDumpPlayer();

	/** Prints the current match phase and player count. */
	UFUNCTION(Exec)
	void GTDumpMatch();

	/** Forces the match to start, skipping the minimum player count. Server only. */
	UFUNCTION(Exec)
	void GTStartMatch();

	/** Forces the match to end immediately. Server only. */
	UFUNCTION(Exec)
	void GTEndMatch();
};
