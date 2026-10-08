// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"

/**
 * Command set for the project's editor UI.
 *
 * Declaring commands here rather than wiring buttons directly gives every entry a name, a
 * tooltip, and a rebindable keyboard shortcut in Editor Preferences for free.
 */
class FGTEditorCommands : public TCommands<FGTEditorCommands>
{
public:

	FGTEditorCommands();

	/* TCommands interface. */
	virtual void RegisterCommands() override;
	/* TCommands interface. */

	/** Opens Project Settings at the GantryExamples section. */
	TSharedPtr<FUICommandInfo> OpenProjectSettings;

	/** Opens Editor Preferences at the GantryExamples section. */
	TSharedPtr<FUICommandInfo> OpenEditorSettings;

	/** Runs data validation across the project's content. */
	TSharedPtr<FUICommandInfo> ValidateProjectAssets;
};
