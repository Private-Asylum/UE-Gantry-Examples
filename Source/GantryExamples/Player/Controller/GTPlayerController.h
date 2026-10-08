// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Player/GTPlayer.h"

#include "GameFramework/PlayerController.h"

#include "GTPlayerController.generated.h"

class UGTInputConfig;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

/**
 * Project player controller.
 *
 * Exists on the server for every player and on each client for its own player only. It owns input,
 * camera ownership and the client's view of the world, so it is the natural home for anything
 * that is "this player's decision" rather than "this body's capability".
 *
 * Input mapping contexts are pushed here rather than on the pawn, so they survive possession
 * changes and death.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AGTPlayerController();

	/* AActor interface. */
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;
	/* AActor interface. */

	/* AController interface. */
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void InitPlayerState() override;
	virtual void OnRep_PlayerState() override;
	/* AController interface. */

	/* APlayerController interface. */
	virtual void SetupInputComponent() override;
	virtual void SetPlayer(UPlayer* InPlayer) override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void AcknowledgePossession(APawn* InPawn) override;
	virtual void ReceivedPlayer() override;
	virtual void UpdateRotation(float DeltaTime) override;
	virtual void AddCheats(bool bForce = false) override;
	/* APlayerController interface. */

	/** Current ready state for this player. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Player")
	EGTPlayerReadyState GetReadyState() const { return ReadyState; }

	/** Fired locally once PlayerState is valid, on both the server and the owning client. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Player")
	FGTOnPlayerStateReady OnPlayerStateReady;

	/** Fired whenever GetReadyState changes. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Player")
	FGTOnPlayerReadyStateChanged OnReadyStateChanged;

	// ==================================================
	// Input
	// ==================================================

	/** Adds a mapping context for this player. Higher priority wins conflicts. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Input")
	void AddInputMappingContext(UInputMappingContext* MappingContext, int32 Priority = 0);

	/** Removes a previously added mapping context. Safe to call when it was never added. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Input")
	void RemoveInputMappingContext(UInputMappingContext* MappingContext);

protected:

	/** Binds actions from InputConfig. Override to add project-specific bindings. */
	virtual void BindInputActions();

	/** Pushes the mapping contexts from the developer settings plus DefaultInputConfig. */
	virtual void ApplyDefaultInputMappings();

	/** Returns the Enhanced Input subsystem for this controller's local player, or nullptr. */
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;

	/** Updates ReadyState and notifies listeners if it changed. */
	void SetReadyState(EGTPlayerReadyState NewState);

	/** Tag-to-action bindings used by this controller. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|Input")
	TObjectPtr<const UGTInputConfig> InputConfig;

private:

	/** Runs the one-time work that needs a valid PlayerState. Safe to call more than once. */
	void HandlePlayerStateReady();

	/** Backing store for GetReadyState. */
	EGTPlayerReadyState ReadyState;

	/** Guards HandlePlayerStateReady so it only fires once per controller. */
	bool bBroadcastPlayerStateReady;
};
