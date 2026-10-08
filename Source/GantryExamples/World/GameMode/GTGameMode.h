// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "World/GTWorld.h"
#include "World/GameMode/GTGameModeBase.h"

#include "GameFramework/GameMode.h"

#include "GTGameMode.generated.h"

/**
 * Gameplay game mode, with the engine's match state machine.
 *
 * Server authoritative and never replicated: it decides the rules, then publishes the results
 * through AGTGameState. Clients must not assume this object exists.
 *
 * Note this derives from AGameMode rather than AGTGameModeBase, because AGameMode is where the
 * match flow lives. AGTGameModeBase is its sibling, not its parent, and exists for maps that do
 * not want that flow.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AGTGameMode();

	/* AGameModeBase interface. */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void GenericPlayerInitialization(AController* C) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	/* AGameModeBase interface. */

	/* AGameMode interface. */
	virtual void HandleMatchIsWaitingToStart() override;
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void HandleMatchHasStarted() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	virtual void HandleMatchHasEnded() override;
	virtual void HandleMatchAborted() override;
	virtual void OnMatchStateSet() override;
	/* AGameMode interface. */

	/** Current match phase, mirrored from the engine MatchState. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Game Mode")
	EGTMatchPhase GetMatchPhase() const;

protected:

	/** Minimum number of connected players before the match will start. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|Match", meta = (ClampMin = "1"))
	int32 MinimumPlayersToStart;

	/** Match length in seconds. Zero means the match runs until something else ends it. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|Match", meta = (ClampMin = "0.0", Units = "s"))
	float MatchDurationSeconds;

	/** World time at which HandleMatchHasStarted ran, or negative if the match is not live. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "GantryExamples|Match")
	float MatchStartWorldTime;
};
