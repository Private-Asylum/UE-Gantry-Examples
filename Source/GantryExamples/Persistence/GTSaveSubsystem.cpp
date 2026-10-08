// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Persistence/GTSaveSubsystem.h"

#include "Core/GTCore.h"
#include "Core/Settings/GTDeveloperSettings.h"
#include "GantryExamplesLogCategories.h"
#include "Persistence/GTSaveGame.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void UGTSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CreateNewSave();

	WorldInitHandle = FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UGTSaveSubsystem::HandleWorldInitialized);
}

void UGTSaveSubsystem::Deinitialize()
{
	if (WorldInitHandle.IsValid())
	{
		FWorldDelegates::OnPostWorldInitialization.Remove(WorldInitHandle);
		WorldInitHandle.Reset();
	}

	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		if (const UWorld* World = GameInstance->GetWorld())
		{
			World->GetTimerManager().ClearTimer(AutosaveTimerHandle);
		}
	}

	Super::Deinitialize();
}

TSubclassOf<UGTSaveGame> UGTSaveSubsystem::ResolveSaveGameClass() const
{
	if (const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get())
	{
		if (UClass* Configured = Settings->SaveGameClass.TryLoadClass<UGTSaveGame>())
		{
			return Configured;
		}
	}

	return UGTSaveGame::StaticClass();
}

UGTSaveGame* UGTSaveSubsystem::CreateNewSave()
{
	CurrentSave = Cast<UGTSaveGame>(UGameplayStatics::CreateSaveGameObject(ResolveSaveGameClass()));

	return CurrentSave;
}

void UGTSaveSubsystem::SaveToSlotAsync(const FString& SlotName)
{
	if (!CurrentSave)
	{
		UE_LOG(LogGTSave, Warning, TEXT("SaveToSlotAsync called with no current save."));
		OnSaveComplete.Broadcast(SlotName, false);
		return;
	}

	if (bOperationInFlight)
	{
		UE_LOG(LogGTSave, Warning, TEXT("SaveToSlotAsync ignored; another operation is in flight."));
		OnSaveComplete.Broadcast(SlotName, false);
		return;
	}

	bOperationInFlight = true;

	CurrentSave->SavedAtUtc = FDateTime::UtcNow();

	if (const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get())
	{
		CurrentSave->WrittenByBuildId = Settings->BuildId;
	}

	FAsyncSaveGameToSlotDelegate Completed;
	Completed.BindWeakLambda(this, [this](const FString& CompletedSlot, const int32 UserIndex, bool bSucceeded)
	{
		bOperationInFlight = false;

		UE_LOG(LogGTSave, Log, TEXT("Save to slot '%s' %s."), *CompletedSlot, bSucceeded ? TEXT("succeeded") : TEXT("failed"));

		OnSaveComplete.Broadcast(CompletedSlot, bSucceeded);
	});

	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, Completed);
}

void UGTSaveSubsystem::LoadFromSlotAsync(const FString& SlotName)
{
	if (bOperationInFlight)
	{
		UE_LOG(LogGTSave, Warning, TEXT("LoadFromSlotAsync ignored; another operation is in flight."));
		OnLoadComplete.Broadcast(SlotName, false);
		return;
	}

	if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UE_LOG(LogGTSave, Log, TEXT("No save in slot '%s'; keeping the current one."), *SlotName);
		OnLoadComplete.Broadcast(SlotName, false);
		return;
	}

	bOperationInFlight = true;

	FAsyncLoadGameFromSlotDelegate Completed;
	Completed.BindWeakLambda(this, [this](const FString& CompletedSlot, const int32 UserIndex, USaveGame* Loaded)
	{
		bOperationInFlight = false;

		UGTSaveGame* LoadedSave = Cast<UGTSaveGame>(Loaded);

		if (!LoadedSave)
		{
			UE_LOG(LogGTSave, Error, TEXT("Slot '%s' did not contain an GTSaveGame."), *CompletedSlot);
			OnLoadComplete.Broadcast(CompletedSlot, false);
			return;
		}

		if (!LoadedSave->MigrateToCurrentVersion())
		{
			OnLoadComplete.Broadcast(CompletedSlot, false);
			return;
		}

		CurrentSave = LoadedSave;

		UE_LOG(LogGTSave, Log, TEXT("Loaded save from slot '%s'."), *CompletedSlot);

		OnLoadComplete.Broadcast(CompletedSlot, true);
	});

	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, Completed);
}

void UGTSaveSubsystem::HandleWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS)
{
	// Only the world this game instance is actually running matters; PIE and editor preview
	// worlds share the process but not the session.
	if (World && GetGameInstance() && World->GetGameInstance() == GetGameInstance())
	{
		ScheduleAutosave(World);
	}
}

void UGTSaveSubsystem::ScheduleAutosave(UWorld* World)
{
	const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get();

	if (!Settings || !World || Settings->AutosaveIntervalSeconds <= 0.0f)
	{
		return;
	}

	World->GetTimerManager().SetTimer(
		AutosaveTimerHandle, this, &UGTSaveSubsystem::HandleAutosave,
		Settings->AutosaveIntervalSeconds, /*bLoop*/ true);
}

void UGTSaveSubsystem::HandleAutosave()
{
	SaveToSlotAsync(GTCore::DefaultSaveSlotName);
}
