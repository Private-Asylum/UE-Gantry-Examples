// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GTPawn.generated.h"

/**
 * Category root for Pawn.
 *
 * A pawn is a body, not a player. It is destroyed on death, replaced on respawn and swapped when
 * the player enters a vehicle, so it must never own anything that has to survive those events.
 * Score, team and loadout belong on the player state; input mappings belong on the controller.
 *
 * The types below describe what a body can do, which is the pawn's actual business.
 */

/** Movement stance, driving speed and capsule size in UGTCharacterMovementComponent. */
UENUM(BlueprintType)
enum class EGTMovementStance : uint8
{
	Walking		UMETA(DisplayName = "Walking"),
	Crouching	UMETA(DisplayName = "Crouching"),
	Sprinting	UMETA(DisplayName = "Sprinting")
};

/** Fired when a pawn's movement stance changes on any machine. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGTOnMovementStanceChanged, EGTMovementStance, OldStance, EGTMovementStance, NewStance);
