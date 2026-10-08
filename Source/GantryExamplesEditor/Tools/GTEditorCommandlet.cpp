// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Tools/GTEditorCommandlet.h"

#include "GantryExamplesEditorLogCategories.h"
#include "Tools/GTEditorUtilityLibrary.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"

UGTEditorCommandlet::UGTEditorCommandlet()
{
	IsClient = false;
	IsServer = false;
	IsEditor = true;
	LogToConsole = true;
	ShowErrorCount = true;
}

int32 UGTEditorCommandlet::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> ParamsMap;

	ParseCommandLine(*Params, Tokens, Switches, ParamsMap);

	const FString* PathParam = ParamsMap.Find(TEXT("path"));
	const FString ScanPath = PathParam ? *PathParam : TEXT("/Game");

	UE_LOG(LogGTEditorTools, Display, TEXT("Auditing %s."), *ScanPath);

	// The asset registry is still scanning at this point in a commandlet; wait it out or the
	// results are whatever happened to be indexed so far.
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().SearchAllAssets(/*bSynchronousSearch*/ true);

	const TArray<FString> Violations = UGTEditorUtilityLibrary::FindAssetNamingViolations(ScanPath);

	for (const FString& Violation : Violations)
	{
		UE_LOG(LogGTEditorTools, Error, TEXT("%s"), *Violation);
	}

	UE_LOG(LogGTEditorTools, Display, TEXT("Audit complete. %d violation(s)."), Violations.Num());

	return Violations.IsEmpty() ? 0 : 1;
}
