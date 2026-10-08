// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/GameNetworkManager.h"

#include "GTGameNetworkManager.generated.h"

/**
 * Per-world network policy: bandwidth, movement error tolerance and standby cheat detection.
 *
 * Spawned by the world from AGTWorldSettings::GameNetworkManagerClass. The movement error
 * thresholds here decide how far a client may drift from the server before being corrected, which
 * is the difference between forgiving netcode and visible rubber banding.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTGameNetworkManager : public AGameNetworkManager
{
	GENERATED_BODY()

public:

	AGTGameNetworkManager();

	/* AActor interface. */
	virtual void PostInitializeComponents() override;
	/* AActor interface. */

	/* AGameNetworkManager interface. */
	virtual bool ExceedsAllowablePositionError(FVector LocDiff) const override;
	virtual void StandbyCheatDetected(EStandbyType StandbyType) override;
	/* AGameNetworkManager interface. */
};
