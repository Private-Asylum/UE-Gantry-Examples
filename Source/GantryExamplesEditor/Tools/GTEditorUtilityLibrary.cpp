// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Tools/GTEditorUtilityLibrary.h"

#include "GantryExamplesEditorLogCategories.h"
#include "Settings/GTEditorSettings.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Modules/ModuleManager.h"

TArray<FAssetData> UGTEditorUtilityLibrary::GetAssetsInPath(const FString& PackagePath, bool bRecursive)
{
	TArray<FAssetData> Assets;

	const FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	AssetRegistryModule.Get().GetAssetsByPath(FName(*PackagePath), Assets, bRecursive);

	return Assets;
}

FString UGTEditorUtilityLibrary::GetExpectedPrefixForAsset(const FAssetData& AssetData)
{
	const UGTEditorSettings* Settings = UGTEditorSettings::Get();

	if (!Settings || !AssetData.IsValid())
	{
		return FString();
	}

	const FString ClassName = AssetData.AssetClassPath.GetAssetName().ToString();

	if (const FString* Prefix = Settings->AssetNamePrefixesByClass.Find(ClassName))
	{
		return *Prefix;
	}

	return FString();
}

bool UGTEditorUtilityLibrary::IsPathIgnoredByValidation(const FString& PackagePath)
{
	const UGTEditorSettings* Settings = UGTEditorSettings::Get();

	if (!Settings)
	{
		return false;
	}

	for (const FString& IgnorePath : Settings->ValidationIgnorePaths)
	{
		if (!IgnorePath.IsEmpty() && PackagePath.StartsWith(IgnorePath))
		{
			return true;
		}
	}

	return false;
}

TArray<FString> UGTEditorUtilityLibrary::FindAssetNamingViolations(const FString& PackagePath)
{
	TArray<FString> Violations;

	const UGTEditorSettings* Settings = UGTEditorSettings::Get();

	if (!Settings || !Settings->bEnforceAssetNamingConventions)
	{
		return Violations;
	}

	for (const FAssetData& AssetData : GetAssetsInPath(PackagePath, /*bRecursive*/ true))
	{
		if (IsPathIgnoredByValidation(AssetData.PackagePath.ToString()))
		{
			continue;
		}

		const FString ExpectedPrefix = GetExpectedPrefixForAsset(AssetData);

		if (ExpectedPrefix.IsEmpty())
		{
			// No convention configured for this class; not a violation.
			continue;
		}

		const FString AssetName = AssetData.AssetName.ToString();

		if (!AssetName.StartsWith(ExpectedPrefix))
		{
			Violations.Add(FString::Printf(TEXT("%s should start with '%s' (%s)"),
				*AssetData.GetObjectPathString(), *ExpectedPrefix,
				*AssetData.AssetClassPath.GetAssetName().ToString()));
		}
	}

	UE_LOG(LogGTEditorValidation, Log, TEXT("%d naming violation(s) under %s."), Violations.Num(), *PackagePath);

	return Violations;
}
