// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GantryExamplesEditorLogCategories.h"

#include "Modules/ModuleManager.h"

class FGTEditorMenus;

/**
 * Editor module for GantryExamples.
 *
 * Loads only in editor targets, so anything here is free of cook and runtime cost. It owns the
 * project's editor UI registration: the Slate style set, the command list, and the tool menu
 * entries. Editor tooling that needs a UObject lifetime belongs in UGTEditorSubsystem instead.
 */
class FGantryExamplesEditorModule : public IModuleInterface
{
public:

	/* IModuleInterface interface. */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }
	/* IModuleInterface interface. */

	/** Convenience accessor. Returns nullptr if the module is not loaded. */
	static FGantryExamplesEditorModule* GetPtr()
	{
		return FModuleManager::GetModulePtr<FGantryExamplesEditorModule>(TEXT("GantryExamplesEditor"));
	}

	/** Command list shared by the toolbar and menu entries. */
	TSharedPtr<class FUICommandList> GetCommandList() const { return CommandList; }

private:

	/** Registers tool menu entries. Deferred until ToolMenus is ready. */
	void RegisterMenus();

	/** Maps commands to their handlers. */
	void BindCommands();

	/** Shared command list for every entry this module registers. */
	TSharedPtr<FUICommandList> CommandList;

	/** Menu registration helper. */
	TSharedPtr<FGTEditorMenus> Menus;
};
