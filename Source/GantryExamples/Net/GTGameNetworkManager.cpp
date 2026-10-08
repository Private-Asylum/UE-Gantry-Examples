// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Net/GTGameNetworkManager.h"

#include "GantryExamplesLogCategories.h"

AGTGameNetworkManager::AGTGameNetworkManager()
{
	// Off by default: false positives kick legitimate players on poor connections. Turn it on
	// once the project has real telemetry to tune the thresholds against.
	bIsStandbyCheckingEnabled = false;
}

void AGTGameNetworkManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

bool AGTGameNetworkManager::ExceedsAllowablePositionError(FVector LocDiff) const
{
	return Super::ExceedsAllowablePositionError(LocDiff);
}

void AGTGameNetworkManager::StandbyCheatDetected(EStandbyType StandbyType)
{
	UE_LOG(LogGTNet, Warning, TEXT("Standby cheat detected, type %d."), static_cast<int32>(StandbyType));

	Super::StandbyCheatDetected(StandbyType);
}
