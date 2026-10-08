// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "World/GTWorld.h"

#include "GameFramework/GameState.h"

#include "GTGameState.generated.h"

/**
 * Replicated state for a match-driven game, paired with AGTGameMode.
 *
 * Adds a Blueprint-friendly match phase on top of the engine's replicated MatchState FName, and
 * a replicated match clock clients can read without asking the server.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTGameState : public AGameState
{
	GENERATED_BODY()

public:

	AGTGameState();

	/* AGameStateBase interface. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/* AGameStateBase interface. */

	/* AGameState interface. */
	virtual void OnRep_MatchState() override;
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	/* AGameState interface. */

	/** Blueprint-friendly view of the replicated MatchState. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Match")
	EGTMatchPhase GetMatchPhase() const { return GTWorld::MatchStateToPhase(GetMatchState()); }

	/** Seconds of match time remaining, or a negative value when the match is untimed. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Match")
	float GetMatchTimeRemaining() const;

	/** Fired on every machine when the replicated match phase changes. Blueprint friendly. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Match")
	FGTOnMatchPhaseChanged OnMatchPhaseChanged;

	/** Native counterpart of OnMatchPhaseChanged. */
	FGTOnMatchPhaseChangedNative OnMatchPhaseChangedNative;

	/** Server world time at which the current match ends. Negative means untimed. */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GantryExamples|Match")
	float MatchEndServerTime;

protected:

	/**
	 * Single funnel for phase change notification.
	 *
	 * OnRep_MatchState routes into the Handle* methods for known states, so this can be reached
	 * twice for one transition. The cached phase below makes it idempotent.
	 */
	void BroadcastMatchPhase();

	/** Last phase actually broadcast, used to suppress duplicate notifications. */
	EGTMatchPhase LastBroadcastPhase;
};
