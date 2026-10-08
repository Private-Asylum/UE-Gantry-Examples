// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Engine/GameEngine.h"

#include "GTGameEngine.generated.h"

/**
 * Project engine class for standalone and cooked builds.
 *
 * Wired up via [/Script/Engine.Engine] GameEngine= in DefaultEngine.ini. This is the earliest
 * hook the project owns: it exists before any world, game instance or local player does, so it
 * is the right home for process-wide policy such as network failure handling and tick rate
 * clamping. The editor uses UUnrealEdEngine instead, so keep gameplay logic out of here.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTGameEngine : public UGameEngine
{
	GENERATED_BODY()

public:

	/* UEngine interface. */
	virtual void Init(IEngineLoop* InEngineLoop) override;
	virtual void Start() override;
	virtual void PreExit() override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;
	/* UEngine interface. */

protected:

	/** Applies project defaults that are easier to express in code than in ini files. */
	virtual void ApplyProjectEngineDefaults();

	/**
	 * Network and travel failure handling.
	 *
	 * UEngine's HandleNetworkFailure_NotifyGameInstance hooks are private, so these are bound to
	 * the public OnNetworkFailure / OnTravelFailure events in Init instead.
	 */
	virtual void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	virtual void HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString);
};
