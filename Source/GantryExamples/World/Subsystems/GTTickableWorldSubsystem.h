// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Subsystems/WorldSubsystem.h"

#include "GTTickableWorldSubsystem.generated.h"

/**
 * Base class for world subsystems that need a per-frame tick.
 *
 * Prefer UGTWorldSubsystem plus a timer where you can; a subsystem that ticks every frame costs
 * every frame, whether or not it has work to do. This exists for the cases that genuinely need
 * frame granularity, and it defaults to not ticking until the world has begun play.
 */
UCLASS(Abstract)
class GANTRYEXAMPLES_API UGTTickableWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* USubsystem interface. */

	/* UWorldSubsystem interface. */
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	/* UWorldSubsystem interface. */

	/* FTickableGameObject interface. */
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	/* FTickableGameObject interface. */

protected:

	/** Per-frame work. Only called once the world has begun play. */
	virtual void TickSubsystem(float DeltaTime) {}

	/** True once OnWorldBeginPlay has run, gating Tick. */
	bool bWorldHasBegunPlay = false;
};
