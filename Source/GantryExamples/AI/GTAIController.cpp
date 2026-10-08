// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "AI/GTAIController.h"

#include "GantryExamplesLogCategories.h"

AGTAIController::AGTAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// AI does not need a player state, and creating one costs replication bandwidth.
	bWantsPlayerState = false;
}

void AGTAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AGTAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogGTAI, Verbose, TEXT("%s possessed %s."), *GetName(), *GetNameSafe(InPawn));
}

void AGTAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AGTAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	Super::UpdateControlRotation(DeltaTime, bUpdatePawn);
}
