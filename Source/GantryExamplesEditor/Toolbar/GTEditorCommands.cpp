// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Toolbar/GTEditorCommands.h"

#include "Toolbar/GTEditorStyle.h"

#define LOCTEXT_NAMESPACE "GTEditorCommands"

FGTEditorCommands::FGTEditorCommands()
	: TCommands<FGTEditorCommands>(
		TEXT("GantryExamplesEditor"),
		NSLOCTEXT("Contexts", "GantryExamplesEditor", "GantryExamples Editor"),
		NAME_None,
		FGTEditorStyle::GetStyleSetName())
{
}

void FGTEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenProjectSettings, "Project Settings",
		"Opens Project Settings at the GantryExamples section.",
		EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(OpenEditorSettings, "Editor Settings",
		"Opens Editor Preferences at the GantryExamples section.",
		EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(ValidateProjectAssets, "Validate Assets",
		"Runs data validation across the project's content.",
		EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
