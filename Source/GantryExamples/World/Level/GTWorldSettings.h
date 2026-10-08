// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/WorldSettings.h"

#include "GTWorldSettings.generated.h"

class UGTSaveGame;

/**
 * Per-map settings actor.
 *
 * Wired up via [/Script/Engine.Engine] WorldSettingsClassName=. Exactly one exists per level and
 * it is the only place to hang authored, per-map data that is not gameplay state: which network
 * manager to use, which music to play, whether the map counts as a front end.
 *
 * Level designers edit this from World Settings, so anything a designer should be able to set
 * per map without touching a game mode belongs here.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	AGTWorldSettings();

	/* AActor interface. */
	virtual void PostInitializeComponents() override;
#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif
	/* AActor interface. */

	/** True when this map is a front end / menu map rather than a gameplay map. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GantryExamples")
	bool bIsFrontEndMap;

	/** Optional display name shown on loading screens. Falls back to the map's asset name. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GantryExamples")
	FText MapDisplayName;

	/** Player starts tagged with this value are preferred by AGTGameMode. Empty means no preference. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GantryExamples")
	FName PreferredPlayerStartTag;
};
