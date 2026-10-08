// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/SaveGame.h"

#include "GTSaveGame.generated.h"

/**
 * Serialised player progress.
 *
 * Every UPROPERTY here is written to disk, so treat the layout as a file format: renaming a
 * property silently loses the old data unless a core redirect is added, and reordering is fine
 * but retyping is not. SaveVersion exists so migration code has something to branch on.
 */
UCLASS(BlueprintType)
class GANTRYEXAMPLES_API UGTSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UGTSaveGame();

	/** Version of the layout this instance was written with. Bump when the format changes. */
	UPROPERTY(BlueprintReadOnly, Category = "GantryExamples|Save")
	int32 SaveVersion;

	/** Build id that wrote this save, for diagnosing version-specific corruption. */
	UPROPERTY(BlueprintReadOnly, Category = "GantryExamples|Save")
	FString WrittenByBuildId;

	/** UTC timestamp of the write. */
	UPROPERTY(BlueprintReadOnly, Category = "GantryExamples|Save")
	FDateTime SavedAtUtc;

	/** Map the player was last in, restored on continue. */
	UPROPERTY(BlueprintReadWrite, Category = "GantryExamples|Save")
	FSoftObjectPath LastPlayedMap;

	/** Total seconds of play recorded across all sessions. */
	UPROPERTY(BlueprintReadWrite, Category = "GantryExamples|Save")
	double TotalPlayTimeSeconds;

	/** Current layout version written by this build. */
	static constexpr int32 CurrentSaveVersion = 1;

	/** Migrates an older layout forward. Returns false when the save is unreadable. */
	virtual bool MigrateToCurrentVersion();
};
