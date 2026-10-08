// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Assets/GTAssetManager.h"

#include "GantryExamplesLogCategories.h"

#include "Engine/Engine.h"

UGTAssetManager::UGTAssetManager()
{
}

UGTAssetManager* UGTAssetManager::GetPtr()
{
	return GEngine ? Cast<UGTAssetManager>(GEngine->AssetManager) : nullptr;
}

void UGTAssetManager::StartInitialLoading()
{
	// Gantry's implementation opens the ledger scope that records the primary asset scan, so any
	// project work added here is nested inside it automatically.
	Super::StartInitialLoading();

	UE_LOG(LogGTCore, Log, TEXT("GantryExamples asset manager ready."));
}
