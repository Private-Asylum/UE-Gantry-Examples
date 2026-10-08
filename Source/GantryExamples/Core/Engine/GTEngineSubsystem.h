// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Subsystems/EngineSubsystem.h"

#include "GTEngineSubsystem.generated.h"

/**
 * Engine-scope subsystem: one instance for the whole process, created before any game instance
 * and destroyed at shutdown. Survives PIE sessions, map travel and game instance teardown.
 *
 * Use it for things that genuinely outlive a session, such as platform service handles or a
 * process-wide cache. Anything that should reset between sessions belongs in
 * UGTGameInstanceSubsystem instead.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* USubsystem interface. */

	/** Wall clock seconds since this subsystem was initialised. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Engine")
	double GetProcessUptimeSeconds() const;

private:

	/** FPlatformTime::Seconds at initialisation, used as the uptime baseline. */
	double InitialiseTimeSeconds = 0.0;
};
