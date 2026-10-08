// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Engine/GTGameEngine.h"

#include "GantryExamplesLogCategories.h"

void UGTGameEngine::Init(IEngineLoop* InEngineLoop)
{
	UE_LOG(LogGTCore, Log, TEXT("GTGameEngine initialising."));

	Super::Init(InEngineLoop);

	OnNetworkFailure().AddUObject(this, &UGTGameEngine::HandleNetworkFailure);
	OnTravelFailure().AddUObject(this, &UGTGameEngine::HandleTravelFailure);

	ApplyProjectEngineDefaults();
}

void UGTGameEngine::Start()
{
	UE_LOG(LogGTCore, Log, TEXT("GTGameEngine starting."));

	Super::Start();
}

void UGTGameEngine::PreExit()
{
	UE_LOG(LogGTCore, Log, TEXT("GTGameEngine shutting down."));

	Super::PreExit();
}

void UGTGameEngine::Tick(float DeltaSeconds, bool bIdleMode)
{
	Super::Tick(DeltaSeconds, bIdleMode);
}

void UGTGameEngine::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogGTNet, Error, TEXT("Network failure: %s (%s)"), ENetworkFailure::ToString(FailureType), *ErrorString);
}

void UGTGameEngine::HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogGTNet, Error, TEXT("Travel failure: %s (%s)"), ETravelFailure::ToString(FailureType), *ErrorString);
}

void UGTGameEngine::ApplyProjectEngineDefaults()
{
	// Deliberately empty. Put anything here that must be true of the process regardless of which
	// map or game mode is running, and that would be awkward to express as a config default.
}
