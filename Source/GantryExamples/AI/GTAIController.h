// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "AIController.h"

#include "GTAIController.generated.h"

/**
 * Base AI controller.
 *
 * Also wired up as the project default via [/Script/Engine.Engine] AIControllerClassName=, so any
 * pawn spawned without an explicit controller class gets this one.
 *
 * An AI controller is the counterpart to a player controller: it owns the decisions, the pawn owns
 * the body. Perception, blackboard and behaviour tree ownership all belong here, never on the pawn.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTAIController : public AAIController
{
	GENERATED_BODY()

public:

	AGTAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/* AActor interface. */
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	/* AActor interface. */

	/* AAIController interface. */
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;
	/* AAIController interface. */
};
