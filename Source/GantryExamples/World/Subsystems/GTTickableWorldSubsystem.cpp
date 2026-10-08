// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/Subsystems/GTTickableWorldSubsystem.h"

#include "GantryExamplesLogCategories.h"

#include "Engine/World.h"

bool UGTTickableWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	return !GetClass()->HasAnyClassFlags(CLASS_Abstract);
}

bool UGTTickableWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGTTickableWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGTTickableWorldSubsystem::Deinitialize()
{
	bWorldHasBegunPlay = false;

	Super::Deinitialize();
}

void UGTTickableWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	bWorldHasBegunPlay = true;
}

bool UGTTickableWorldSubsystem::IsTickable() const
{
	return bWorldHasBegunPlay && !IsTemplate() && Super::IsTickable();
}

void UGTTickableWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickSubsystem(DeltaTime);
}

TStatId UGTTickableWorldSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGTTickableWorldSubsystem, STATGROUP_Tickables);
}
