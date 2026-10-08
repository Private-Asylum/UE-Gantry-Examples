// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Subsystems/WorldSubsystem.h"

#include "GTWorldSubsystem.generated.h"

/**
 * Base class for world-scoped subsystems.
 *
 * One instance per UWorld, created before the world begins play and destroyed with it. This is
 * the modern replacement for the "manager actor placed in every level" pattern: no actor to
 * forget to place, no null checks, and a typed getter from any world context object.
 *
 * Note this is created for editor preview worlds and inactive worlds too, which is rarely what
 * gameplay code wants, so DoesSupportWorldType is narrowed to game and PIE worlds by default.
 */
UCLASS(Abstract)
class GANTRYEXAMPLES_API UGTWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void PostInitialize() override;
	/* USubsystem interface. */

	/* UWorldSubsystem interface. */
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void OnWorldComponentsUpdated(UWorld& World) override;
	/* UWorldSubsystem interface. */

protected:

	/** Override to opt a subsystem out of dedicated server builds. */
	virtual bool ShouldCreateOnDedicatedServer() const { return true; }

	/** Override to opt a subsystem out of client builds. */
	virtual bool ShouldCreateOnClient() const { return true; }
};
