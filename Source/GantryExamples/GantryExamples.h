// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GantryExamplesLogCategories.h"

#include "Modules/ModuleManager.h"

/**
 * Primary game module for GantryExamples.
 *
 * Owns anything that has to exist before the first world does and after the last one is gone:
 * console command registration, engine delegate hookups, and native subsystem bootstrapping.
 */
class FGantryExamplesModule : public FDefaultGameModuleImpl
{
public:

	/* IModuleInterface interface. */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override { return true; }
	/* IModuleInterface interface. */

	/** Convenience accessor. Returns nullptr if the module is not loaded. */
	static FGantryExamplesModule* GetPtr()
	{
		return FModuleManager::GetModulePtr<FGantryExamplesModule>(TEXT("GantryExamples"));
	}

private:

	/** Called once the engine has finished initialising, before the first map loads. */
	void OnPostEngineInit();

	/** Called before module unload, earlier than ShutdownModule and before RHI teardown. */
	void OnPreExit();

	/** Registers the project's `GT.*` console commands. */
	void RegisterConsoleCommands();

	/** Removes every console command registered by RegisterConsoleCommands. */
	void UnregisterConsoleCommands();

	/** Handle for the PostEngineInit callback. */
	FDelegateHandle PostEngineInitHandle;

	/** Handle for the PreExit callback. */
	FDelegateHandle PreExitHandle;

	/** Console commands owned by this module, released on shutdown. */
	TArray<IConsoleObject*> ConsoleCommands;
};
