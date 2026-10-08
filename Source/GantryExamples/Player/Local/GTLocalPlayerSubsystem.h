// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Subsystems/LocalPlayerSubsystem.h"

#include "GTLocalPlayerSubsystem.generated.h"

/**
 * Base class for subsystems scoped to a single local player.
 *
 * One instance per ULocalPlayer, so in split screen each player gets their own. Lives across
 * every map the player sees. Enhanced Input's mapping subsystem works exactly this way, which is
 * a good model for what belongs here: per-human, world-independent state.
 *
 * Never assume a world exists when this initialises.
 */
UCLASS(Abstract)
class GANTRYEXAMPLES_API UGTLocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* USubsystem interface. */

	/** The local player owning this subsystem, typed to the project class. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Player")
	class UGTLocalPlayer* GetGTLocalPlayer() const;
};
