// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/Subsystems/GTWorldSubsystem.h"

#include "GantryExamplesLogCategories.h"

#include "Engine/World.h"

bool UGTWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	if (GetClass()->HasAnyClassFlags(CLASS_Abstract))
	{
		return false;
	}

	if (const UWorld* World = Cast<UWorld>(Outer))
	{
		const ENetMode NetMode = World->GetNetMode();

		if (!ShouldCreateOnDedicatedServer() && NetMode == NM_DedicatedServer)
		{
			return false;
		}

		if (!ShouldCreateOnClient() && NetMode == NM_Client)
		{
			return false;
		}
	}

	return true;
}

bool UGTWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	// Deliberately narrower than the engine default, which also includes editor preview worlds.
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGTWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogGTWorld, Verbose, TEXT("%s initialised."), *GetClass()->GetName());
}

void UGTWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UGTWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UGTWorldSubsystem::OnWorldComponentsUpdated(UWorld& World)
{
	Super::OnWorldComponentsUpdated(World);
}

void UGTWorldSubsystem::Deinitialize()
{
	UE_LOG(LogGTWorld, Verbose, TEXT("%s deinitialised."), *GetClass()->GetName());

	Super::Deinitialize();
}
