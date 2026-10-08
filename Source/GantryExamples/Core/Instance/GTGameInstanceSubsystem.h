// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"

#include "GTGameInstanceSubsystem.generated.h"

/**
 * Base class for game instance scoped subsystems.
 *
 * One instance per game instance, so state survives map travel but is torn down when the session
 * ends. This is the right scope for matchmaking state, a session-long inventory cache, or
 * anything that should reset when the player quits to the main menu.
 *
 * Derive from this rather than UGameInstanceSubsystem directly so every project subsystem picks
 * up the shared creation policy below.
 */
UCLASS(Abstract)
class GANTRYEXAMPLES_API UGTGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* USubsystem interface. */

protected:

	/**
	 * Override to opt a subsystem out of dedicated server builds.
	 * Defaults to true; UI-facing subsystems should return false.
	 */
	virtual bool ShouldCreateOnDedicatedServer() const { return true; }
};
