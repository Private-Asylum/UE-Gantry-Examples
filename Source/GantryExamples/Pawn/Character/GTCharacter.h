// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Pawn/GTPawn.h"

#include "GameFramework/Character.h"

#include "GTCharacter.generated.h"

class UGTCharacterMovementComponent;
class UGTInputConfig;
class UCameraComponent;
class USpringArmComponent;

/**
 * Base playable character.
 *
 * Owns the body: capsule, mesh, movement and the camera rig. Input is bound here on possession
 * rather than on the controller, because these bindings only make sense while this body exists.
 *
 * Anything that must survive death belongs on AGTPlayerState.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AGTCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/* AActor interface. */
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/* AActor interface. */

	/* APawn interface. */
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	/* APawn interface. */

	/* ACharacter interface. */
	virtual void Landed(const FHitResult& Hit) override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	/* ACharacter interface. */

	/** Typed accessor for the movement component. Never null on a spawned character. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Character")
	UGTCharacterMovementComponent* GetGTCharacterMovement() const;

	/** Current stance, replicated so remote clients can drive animation from it. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Character")
	EGTMovementStance GetStance() const { return Stance; }

	/** Server-authoritative stance change. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Character")
	void SetStance(EGTMovementStance NewStance);

	/** Fired on every machine when the stance changes. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Character")
	FGTOnMovementStanceChanged OnStanceChanged;

protected:

	/** Binds this character's actions. Called from SetupPlayerInputComponent. */
	virtual void BindInputActions(class UGTEnhancedInputComponent* GTInputComponent);

	/* Input handlers. Bound by tag through UGTInputConfig. */
	void Input_Move(const struct FInputActionValue& Value);
	void Input_Look(const struct FInputActionValue& Value);
	void Input_JumpStarted();
	void Input_JumpCompleted();
	void Input_CrouchToggle();
	void Input_SprintStarted();
	void Input_SprintCompleted();

	/** Replication callback for Stance. */
	UFUNCTION()
	virtual void OnRep_Stance(EGTMovementStance OldStance);

	/** Third person boom. Detach or hide it for a first person character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GantryExamples|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Camera driven by the boom. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GantryExamples|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Tag-to-action bindings for this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|Input")
	TObjectPtr<const UGTInputConfig> InputConfig;

	/** Current stance, replicated to all machines. */
	UPROPERTY(ReplicatedUsing = OnRep_Stance, BlueprintReadOnly, Category = "GantryExamples|Character")
	EGTMovementStance Stance;
};
