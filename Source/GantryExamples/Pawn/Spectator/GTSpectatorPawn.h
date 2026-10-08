// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/SpectatorPawn.h"

#include "GTSpectatorPawn.generated.h"

/**
 * Pawn used while a player is spectating: dead, waiting to spawn, or in a free camera.
 *
 * Deliberately minimal. It has no collision against pawns, does not replicate movement to other
 * clients, and exists only so the spectating player has something to attach a camera to.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:

	AGTSpectatorPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/* APawn interface. */
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	/* APawn interface. */
};
