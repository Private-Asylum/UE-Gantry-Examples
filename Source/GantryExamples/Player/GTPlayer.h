// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GTPlayer.generated.h"

/**
 * Category root for Player.
 *
 * The player side of the framework is split across four objects with very different lifetimes,
 * and confusing them is the single most common source of "why is this null on the client" bugs:
 *
 *   ULocalPlayer      - one per local human, outlives every map and every controller.
 *   APlayerController - one per player per world, server authoritative, local one is the input owner.
 *   APlayerState      - replicated to everyone, survives respawns and seamless travel.
 *   APawn             - the physical body, freely destroyed and respawned.
 *
 * The types below are shared by all of them.
 */

/** How far along a player is in joining and being ready to play. */
UENUM(BlueprintType)
enum class EGTPlayerReadyState : uint8
{
	/** Controller exists, player state has not replicated yet. */
	Connecting	UMETA(DisplayName = "Connecting"),

	/** Player state is present, no pawn possessed. */
	Ready		UMETA(DisplayName = "Ready"),

	/** Pawn possessed and playing. */
	Playing		UMETA(DisplayName = "Playing"),

	/** Watching rather than playing. */
	Spectating	UMETA(DisplayName = "Spectating"),

	/** Disconnected or being torn down. */
	Leaving		UMETA(DisplayName = "Leaving")
};

/** Fired when a player's ready state changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGTOnPlayerReadyStateChanged, APlayerState*, PlayerState, EGTPlayerReadyState, NewState);

/** Fired by AGTPlayerController once its player state has replicated and is safe to read. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGTOnPlayerStateReady, APlayerState*, PlayerState);
