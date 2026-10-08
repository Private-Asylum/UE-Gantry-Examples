// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FUICommandList;

/**
 * Registers the project's entries into the editor's tool menus.
 *
 * All registration goes through UToolMenus by menu name, so no LevelEditor dependency is needed
 * and entries survive editor layout changes. Every entry is owned by the editor module, which
 * unregisters them wholesale on shutdown.
 */
class FGTEditorMenus : public TSharedFromThis<FGTEditorMenus>
{
public:

	/** Adds the project's menu and toolbar entries, bound to the given command list. */
	void Register(TSharedPtr<FUICommandList> CommandList);

	/* Command handlers. Static so they can be bound without keeping this alive. */

	/** Opens Project Settings at the GantryExamples section. */
	static void OpenProjectSettings();

	/** Opens Editor Preferences at the GantryExamples section. */
	static void OpenEditorSettings();

	/** Runs data validation across the project's content directory. */
	static void ValidateProjectAssets();

private:

	/** Adds the GantryExamples submenu under the Tools menu. */
	void RegisterToolsMenu(TSharedPtr<FUICommandList> CommandList);

	/** Adds a GantryExamples button to the level editor toolbar. */
	void RegisterLevelEditorToolbar(TSharedPtr<FUICommandList> CommandList);
};
