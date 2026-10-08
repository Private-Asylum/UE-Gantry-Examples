// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Toolbar/GTEditorMenus.h"

#include "GantryExamplesEditorLogCategories.h"
#include "Toolbar/GTEditorCommands.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Commands/UICommandList.h"
#include "ISettingsModule.h"
#include "Modules/ModuleManager.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "GTEditorMenus"

void FGTEditorMenus::Register(TSharedPtr<FUICommandList> CommandList)
{
	RegisterToolsMenu(CommandList);
	RegisterLevelEditorToolbar(CommandList);
}

void FGTEditorMenus::RegisterToolsMenu(TSharedPtr<FUICommandList> CommandList)
{
	UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");

	if (!ToolsMenu)
	{
		return;
	}

	FToolMenuSection& Section = ToolsMenu->FindOrAddSection(
		"GantryExamples", LOCTEXT("SectionLabel", "GantryExamples"));

	const FGTEditorCommands& Commands = FGTEditorCommands::Get();

	Section.AddMenuEntryWithCommandList(Commands.OpenProjectSettings, CommandList);
	Section.AddMenuEntryWithCommandList(Commands.OpenEditorSettings, CommandList);
	Section.AddMenuEntryWithCommandList(Commands.ValidateProjectAssets, CommandList);
}

void FGTEditorMenus::RegisterLevelEditorToolbar(TSharedPtr<FUICommandList> CommandList)
{
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");

	if (!ToolbarMenu)
	{
		return;
	}

	FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("GantryExamples");

	FToolMenuEntry Entry = FToolMenuEntry::InitToolBarButton(
		FGTEditorCommands::Get().OpenProjectSettings,
		LOCTEXT("ToolbarLabel", "GantryExamples"),
		LOCTEXT("ToolbarTooltip", "GantryExamples project settings and tools."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Settings"));

	Entry.SetCommandList(CommandList);

	Section.AddEntry(Entry);
}

void FGTEditorMenus::OpenProjectSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->ShowViewer("Project", "Game", "GantryExamples");
	}
}

void FGTEditorMenus::OpenEditorSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->ShowViewer("Editor", "Plugins", "GantryExamplesEditor");
	}
}

void FGTEditorMenus::ValidateProjectAssets()
{
	// The Data Validation plugin owns the actual run; this just points it at the project content.
	UE_LOG(LogGTEditorTools, Log, TEXT("Requesting asset validation for /Game."));

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> Assets;
	AssetRegistryModule.Get().GetAssetsByPath(FName(TEXT("/Game")), Assets, /*bRecursive*/ true);

	UE_LOG(LogGTEditorTools, Log,
		TEXT("%d asset(s) under /Game. Use Tools > Validate Data for the full run with results UI."),
		Assets.Num());
}

#undef LOCTEXT_NAMESPACE
