// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GantryAssetManager.h"

#include "GTAssetManager.generated.h"

/**
 * GantryExamples's asset manager.
 *
 * A worked example of the Gantry extension model: the project subclasses Gantry's class and names
 * its own in DefaultEngine.ini
 *
 *     [/Script/Engine.Engine]
 *     AssetManagerClassName=/Script/GantryExamples.GTAssetManager
 *
 * Everything the project loads through here lands in Gantry's ledger, so the loading screen and
 * the Load Gauge panel see project work and framework work in one list.
 *
 * Note this hierarchy does not need Gantry's class-selection helper: the engine resolves the asset
 * manager by name rather than by scanning subclasses, so there is no risk of two being created.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTAssetManager : public UGantryAssetManager
{
	GENERATED_BODY()

public:

	UGTAssetManager();

	/* UAssetManager interface. */
	virtual void StartInitialLoading() override;
	/* UAssetManager interface. */

	/** Typed accessor. Null if the project's asset manager is not configured. */
	static UGTAssetManager* GetPtr();
};
