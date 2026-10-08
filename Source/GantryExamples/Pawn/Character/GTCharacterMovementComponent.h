// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Pawn/GTPawn.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "GTCharacterMovementComponent.generated.h"

/**
 * Project character movement.
 *
 * Installed by AGTCharacter through the object initialiser, so every GTCharacter gets it without
 * per-Blueprint wiring.
 *
 * A warning before extending this: character movement is client predicted. Any new input that
 * affects movement needs a matching FSavedMove_Character and FNetworkPredictionData_Client entry,
 * or clients and server will disagree and the player will rubber band. The stance below is
 * deliberately server-authoritative and replicated rather than predicted, which is correct for a
 * value that changes rarely; do not copy that approach for per-frame input.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UGTCharacterMovementComponent();

	/* UMovementComponent interface. */
	virtual float GetMaxSpeed() const override;
	/* UMovementComponent interface. */

	/* UCharacterMovementComponent interface. */
	virtual bool CanAttemptJump() const override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	/* UCharacterMovementComponent interface. */

	/** Current stance. Set by the owning character. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Movement")
	EGTMovementStance GetStance() const { return Stance; }

	/** Applies a stance and its associated speed. Call from the owning character only. */
	void SetStance(EGTMovementStance NewStance);

	/** Ground speed used while sprinting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|Movement", meta = (ClampMin = "0.0", Units = "cm/s"))
	float SprintSpeed;

private:

	/** Backing store for GetStance. */
	EGTMovementStance Stance;
};
