// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Core/Instance/GTGameInstanceSubsystem.h"

#include "Engine/World.h"

#include "GTSaveSubsystem.generated.h"

class UGTSaveGame;

/** Fired when a save or load finishes, successfully or not. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGTOnSaveGameComplete, const FString&, SlotName, bool, bSucceeded);

/**
 * Owns the current save game and the async read and write of it.
 *
 * Game instance scoped, so the save survives map travel but is dropped when the session ends.
 * Every write is asynchronous; a synchronous save on the game thread stalls the frame for as long
 * as the platform's storage takes, which on console is a long time.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTSaveSubsystem : public UGTGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* USubsystem interface. */

	/** The loaded save, or a freshly created one. Never null after Initialize. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Save")
	UGTSaveGame* GetCurrentSave() const { return CurrentSave; }

	/** Asynchronously writes the current save to a slot. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Save")
	void SaveToSlotAsync(const FString& SlotName);

	/** Asynchronously reads a slot, replacing the current save on success. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Save")
	void LoadFromSlotAsync(const FString& SlotName);

	/** Discards the current save and starts a new one. Does not touch disk. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Save")
	UGTSaveGame* CreateNewSave();

	/** True while a read or write is in flight. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Save")
	bool IsBusy() const { return bOperationInFlight; }

	/** Fired when SaveToSlotAsync finishes. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Save")
	FGTOnSaveGameComplete OnSaveComplete;

	/** Fired when LoadFromSlotAsync finishes. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Save")
	FGTOnSaveGameComplete OnLoadComplete;

protected:

	/* UGTGameInstanceSubsystem interface. */
	virtual bool ShouldCreateOnDedicatedServer() const override { return false; }
	/* UGTGameInstanceSubsystem interface. */

	/** Resolves the save game class from UGTDeveloperSettings, falling back to UGTSaveGame. */
	TSubclassOf<UGTSaveGame> ResolveSaveGameClass() const;

	/**
	 * Restarts the autosave timer from the interval in UGTDeveloperSettings.
	 *
	 * Timers belong to a world, and subsystems initialise before the first world exists, so this
	 * is driven off world initialisation rather than called once at startup.
	 */
	void ScheduleAutosave(UWorld* World);

	/** Reschedules the autosave timer whenever a game world comes up. */
	void HandleWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS);

	/** Timer callback that writes to the default slot. */
	void HandleAutosave();

	/** The save currently in memory. */
	UPROPERTY(Transient)
	TObjectPtr<UGTSaveGame> CurrentSave;

	/** Handle for the autosave timer. */
	FTimerHandle AutosaveTimerHandle;

	/** Handle for the world initialisation callback. */
	FDelegateHandle WorldInitHandle;

	/** Guards against overlapping reads and writes. */
	bool bOperationInFlight = false;
};
