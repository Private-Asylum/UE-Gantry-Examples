// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "GantryExamples.h"

#include "Core/GantryEngineVersion.h"
#include "Core/Settings/GTDeveloperSettings.h"

#include "HAL/IConsoleManager.h"
#include "Misc/CoreDelegates.h"

#define LOCTEXT_NAMESPACE "FGantryExamplesModule"

void FGantryExamplesModule::StartupModule()
{
	UE_LOG(LogGantryExamples, Log, TEXT("GantryExamples module starting up."));

	PostEngineInitHandle = Gantry::OnPostEngineInit().AddRaw(this, &FGantryExamplesModule::OnPostEngineInit);
	PreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FGantryExamplesModule::OnPreExit);

	RegisterConsoleCommands();
}

void FGantryExamplesModule::ShutdownModule()
{
	UE_LOG(LogGantryExamples, Log, TEXT("GantryExamples module shutting down."));

	UnregisterConsoleCommands();

	if (PostEngineInitHandle.IsValid())
	{
		Gantry::OnPostEngineInit().Remove(PostEngineInitHandle);
		PostEngineInitHandle.Reset();
	}

	if (PreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(PreExitHandle);
		PreExitHandle.Reset();
	}
}

void FGantryExamplesModule::OnPostEngineInit()
{
	// Touch the settings CDO so the project settings section is populated and any config-driven
	// defaults are resolved before the first world is created.
	if (const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get())
	{
		UE_LOG(LogGantryExamples, Log, TEXT("GantryExamples settings loaded. Build id: %s"), *Settings->BuildId);
	}
}

void FGantryExamplesModule::OnPreExit()
{
	// Last chance to release anything that must not outlive the RHI.
	UE_LOG(LogGantryExamples, Log, TEXT("GantryExamples module PreExit."));
}

void FGantryExamplesModule::RegisterConsoleCommands()
{
	ConsoleCommands.Add(IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("GT.DumpSettings"),
		TEXT("Prints the resolved GantryExamples developer settings to the log."),
		FConsoleCommandDelegate::CreateLambda([]()
		{
			if (const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get())
			{
				UE_LOG(LogGantryExamples, Display, TEXT("%s"), *Settings->ToDebugString());
			}
		}),
		ECVF_Default));
}

void FGantryExamplesModule::UnregisterConsoleCommands()
{
	for (IConsoleObject* Command : ConsoleCommands)
	{
		IConsoleManager::Get().UnregisterConsoleObject(Command);
	}

	ConsoleCommands.Empty();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_PRIMARY_GAME_MODULE(FGantryExamplesModule, GantryExamples, "GantryExamples");
