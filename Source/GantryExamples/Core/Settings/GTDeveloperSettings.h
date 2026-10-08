// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Core/GTCore.h"

#include "Engine/DeveloperSettings.h"

#include "GTDeveloperSettings.generated.h"

class UGTSaveGame;
class UInputMappingContext;

/**
 * Project wide settings, surfaced under Project Settings -> Game -> GantryExamples.
 *
 * This is the one place gameplay code should read tunables from. Anything added here is
 * config-backed (DefaultGame.ini), hot-reloadable in the editor, and readable from Blueprint,
 * which beats a pile of static consts or a hand-rolled singleton.
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "GantryExamples"))
class GANTRYEXAMPLES_API UGTDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UGTDeveloperSettings();

	/* UDeveloperSettings interface. */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	virtual FName GetCategoryName() const override { return TEXT("Game"); }
	virtual FName GetSectionName() const override { return TEXT("GantryExamples"); }
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	/* UDeveloperSettings interface. */

	/** Settings are a CDO, so this never returns nullptr once the class is loaded. */
	static const UGTDeveloperSettings* Get() { return GetDefault<UGTDeveloperSettings>(); }

	/** Mutable accessor. Editor and tooling only; runtime code should treat settings as read only. */
	static UGTDeveloperSettings* GetMutable() { return GetMutableDefault<UGTDeveloperSettings>(); }

	/** Human readable dump used by the `GT.DumpSettings` console command. */
	FString ToDebugString() const;

	// ==================================================
	// Build identity
	// ==================================================

	/** Free-form build identifier stamped into logs and save games. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Build")
	FString BuildId;

	/** Controls whether cheats, debug HUD and developer console commands are available. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Build")
	EGTBuildEnvironment BuildEnvironment;

	// ==================================================
	// Bootstrap
	// ==================================================

	/** Map loaded when the game instance finishes initialising. Empty means "use the engine default". */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Bootstrap", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath FrontEndMap;

	/** Input mapping contexts pushed for every local player on possession, lowest priority first. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Bootstrap")
	TArray<TSoftObjectPtr<UInputMappingContext>> DefaultInputMappingContexts;

	// ==================================================
	// Persistence
	// ==================================================

	/** Save game class instantiated by UGTSaveSubsystem. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Persistence", meta = (MetaClass = "/Script/GantryExamples.GTSaveGame"))
	FSoftClassPath SaveGameClass;

	/** Seconds between autosaves. Zero disables autosaving entirely. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Persistence", meta = (ClampMin = "0.0", Units = "s"))
	float AutosaveIntervalSeconds;

	// ==================================================
	// Diagnostics
	// ==================================================

	/** Draws the on-screen debug HUD layer by default. Ignored in Live builds. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Diagnostics")
	bool bShowDebugHUDByDefault;

	/** Returns true when cheats and debug affordances should be permitted for this build. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings")
	bool AllowsCheats() const;
};
