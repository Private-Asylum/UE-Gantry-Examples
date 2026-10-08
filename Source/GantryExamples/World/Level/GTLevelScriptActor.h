// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Engine/LevelScriptActor.h"

#include "GTLevelScriptActor.generated.h"

/**
 * Base class for every level Blueprint in the project.
 *
 * Wired up via [/Script/Engine.Engine] LevelScriptActorClassName=. Every level Blueprint created
 * from now on inherits this, so shared per-level behaviour can be added once here rather than
 * copy-pasted into each level graph. Level Blueprints are a notorious place for logic to go and
 * never be found again; keep this class thin and push real behaviour into subsystems.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	AGTLevelScriptActor();

	/* AActor interface. */
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	/* AActor interface. */
};
