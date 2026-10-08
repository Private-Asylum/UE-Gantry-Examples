// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "GantryExamplesEditor.h"

#include "Settings/GTEditorSettings.h"
#include "Toolbar/GTEditorCommands.h"
#include "Toolbar/GTEditorMenus.h"
#include "Toolbar/GTEditorStyle.h"

#include "Framework/Commands/UICommandList.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FGantryExamplesEditorModule"

void FGantryExamplesEditorModule::StartupModule()
{
	UE_LOG(LogGantryExamplesEditor, Log, TEXT("GantryExamplesEditor module starting up."));

	FGTEditorStyle::Initialize();
	FGTEditorStyle::ReloadTextures();

	FGTEditorCommands::Register();

	CommandList = MakeShared<FUICommandList>();
	BindCommands();

	Menus = MakeShared<FGTEditorMenus>();

	// ToolMenus may not exist yet during module load, so defer registration.
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGantryExamplesEditorModule::RegisterMenus));
}

void FGantryExamplesEditorModule::ShutdownModule()
{
	UE_LOG(LogGantryExamplesEditor, Log, TEXT("GantryExamplesEditor module shutting down."));

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	Menus.Reset();
	CommandList.Reset();

	FGTEditorCommands::Unregister();
	FGTEditorStyle::Shutdown();
}

void FGantryExamplesEditorModule::BindCommands()
{
	const FGTEditorCommands& Commands = FGTEditorCommands::Get();

	CommandList->MapAction(
		Commands.OpenProjectSettings,
		FExecuteAction::CreateStatic(&FGTEditorMenus::OpenProjectSettings),
		FCanExecuteAction());

	CommandList->MapAction(
		Commands.OpenEditorSettings,
		FExecuteAction::CreateStatic(&FGTEditorMenus::OpenEditorSettings),
		FCanExecuteAction());

	CommandList->MapAction(
		Commands.ValidateProjectAssets,
		FExecuteAction::CreateStatic(&FGTEditorMenus::ValidateProjectAssets),
		FCanExecuteAction());
}

void FGantryExamplesEditorModule::RegisterMenus()
{
	// Scopes every menu entry to this module so UnregisterOwner cleans all of them up.
	FToolMenuOwnerScoped OwnerScoped(this);

	if (Menus.IsValid())
	{
		Menus->Register(CommandList);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGantryExamplesEditorModule, GantryExamplesEditor)
