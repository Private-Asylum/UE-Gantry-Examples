// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Pawn/Spectator/GTSpectatorPawn.h"

#include "GantryExamplesLogCategories.h"

AGTSpectatorPawn::AGTSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;
}

void AGTSpectatorPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(LogGTPawn, Verbose, TEXT("Spectator pawn possessed by %s."), *GetNameSafe(NewController));
}

void AGTSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
