// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GTWorld.generated.h"

/**
 * Category root for World.
 *
 * Holds the vocabulary shared by the game mode, game state, world settings and world subsystems
 * underneath this folder. The engine tracks match progress as an FName (MatchState::InProgress and
 * friends), which is replication-friendly but awkward in Blueprint and impossible to switch on.
 * EGTMatchPhase is the project-facing mirror of that, with conversions in both directions.
 */

/** Blueprint-friendly mirror of the engine's MatchState FName. */
UENUM(BlueprintType)
enum class EGTMatchPhase : uint8
{
	/** Actors exist but BeginPlay has not run. */
	EnteringMap		UMETA(DisplayName = "Entering Map"),

	/** Waiting for enough players, or for ReadyToStartMatch to return true. */
	WaitingToStart	UMETA(DisplayName = "Waiting To Start"),

	/** Match is live. */
	InProgress		UMETA(DisplayName = "In Progress"),

	/** Match finished normally; post-match state is being shown. */
	WaitingPostMatch UMETA(DisplayName = "Waiting Post Match"),

	/** Travelling out of the map. */
	LeavingMap		UMETA(DisplayName = "Leaving Map"),

	/** Match ended early, e.g. host disconnect. */
	Aborted			UMETA(DisplayName = "Aborted"),

	/** MatchState was an FName the project does not know about. */
	Unknown			UMETA(DisplayName = "Unknown")
};

/** Fired by AGTGameState when the replicated match phase changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGTOnMatchPhaseChanged, EGTMatchPhase, NewPhase);

/** Native counterpart of FGTOnMatchPhaseChanged. */
DECLARE_MULTICAST_DELEGATE_OneParam(FGTOnMatchPhaseChangedNative, EGTMatchPhase /*NewPhase*/);

namespace GTWorld
{
	/** Converts an engine MatchState FName into the project enum. */
	GANTRYEXAMPLES_API EGTMatchPhase MatchStateToPhase(FName MatchState);

	/** Converts the project enum back into an engine MatchState FName. */
	GANTRYEXAMPLES_API FName PhaseToMatchState(EGTMatchPhase Phase);
}
