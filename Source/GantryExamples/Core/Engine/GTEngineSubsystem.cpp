// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Engine/GTEngineSubsystem.h"

#include "GantryExamplesLogCategories.h"

#include "HAL/PlatformTime.h"

bool UGTEngineSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGTEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InitialiseTimeSeconds = FPlatformTime::Seconds();

	UE_LOG(LogGTCore, Log, TEXT("GTEngineSubsystem initialised."));
}

void UGTEngineSubsystem::Deinitialize()
{
	UE_LOG(LogGTCore, Log, TEXT("GTEngineSubsystem deinitialised after %.1fs."), GetProcessUptimeSeconds());

	Super::Deinitialize();
}

double UGTEngineSubsystem::GetProcessUptimeSeconds() const
{
	return FPlatformTime::Seconds() - InitialiseTimeSeconds;
}
