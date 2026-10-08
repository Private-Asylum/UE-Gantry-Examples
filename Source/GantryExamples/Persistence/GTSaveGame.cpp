// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Persistence/GTSaveGame.h"

#include "GantryExamplesLogCategories.h"

UGTSaveGame::UGTSaveGame()
	: SaveVersion(CurrentSaveVersion)
	, SavedAtUtc(FDateTime::MinValue())
	, TotalPlayTimeSeconds(0.0)
{
}

bool UGTSaveGame::MigrateToCurrentVersion()
{
	if (SaveVersion == CurrentSaveVersion)
	{
		return true;
	}

	if (SaveVersion > CurrentSaveVersion)
	{
		UE_LOG(LogGTSave, Error,
			TEXT("Save was written by a newer build (version %d, this build reads %d). Refusing to load."),
			SaveVersion, CurrentSaveVersion);
		return false;
	}

	// Add a case per version step as the format evolves, oldest first, falling through so a very
	// old save walks the whole chain.
	UE_LOG(LogGTSave, Log, TEXT("Migrating save from version %d to %d."), SaveVersion, CurrentSaveVersion);

	SaveVersion = CurrentSaveVersion;

	return true;
}
