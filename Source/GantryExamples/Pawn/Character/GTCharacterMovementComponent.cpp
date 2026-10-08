// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Pawn/Character/GTCharacterMovementComponent.h"

#include "GantryExamplesLogCategories.h"

UGTCharacterMovementComponent::UGTCharacterMovementComponent()
	: SprintSpeed(900.0f)
	, Stance(EGTMovementStance::Walking)
{
	MaxWalkSpeed = 600.0f;
	MaxWalkSpeedCrouched = 300.0f;
	NavAgentProps.bCanCrouch = true;
	bCanWalkOffLedgesWhenCrouching = true;

	// Orient the mesh to movement rather than to the controller by default; third person games
	// want this, first person games should flip it on the character.
	bOrientRotationToMovement = true;
	RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

float UGTCharacterMovementComponent::GetMaxSpeed() const
{
	if (Stance == EGTMovementStance::Sprinting && IsMovingOnGround())
	{
		return SprintSpeed;
	}

	return Super::GetMaxSpeed();
}

bool UGTCharacterMovementComponent::CanAttemptJump() const
{
	return Super::CanAttemptJump();
}

void UGTCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void UGTCharacterMovementComponent::SetStance(EGTMovementStance NewStance)
{
	if (Stance == NewStance)
	{
		return;
	}

	Stance = NewStance;

	UE_LOG(LogGTPawn, Verbose, TEXT("%s stance is now %d."), *GetNameSafe(GetOwner()), static_cast<int32>(NewStance));
}
