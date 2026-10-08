// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Tools/GTEditorValidator.h"

#include "GantryExamplesEditorLogCategories.h"
#include "Settings/GTEditorSettings.h"
#include "Tools/GTEditorUtilityLibrary.h"

#include "Misc/DataValidation.h"

#define LOCTEXT_NAMESPACE "GTEditorValidator"

UGTEditorValidator::UGTEditorValidator()
{
	bIsEnabled = true;
}

bool UGTEditorValidator::CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InObject,
	FDataValidationContext& InContext) const
{
	const UGTEditorSettings* Settings = UGTEditorSettings::Get();

	if (!Settings || !Settings->bEnforceAssetNamingConventions || !InAssetData.IsValid())
	{
		return false;
	}

	// Only project content; engine and plugin assets are not ours to rename.
	if (!InAssetData.PackageName.ToString().StartsWith(TEXT("/Game")))
	{
		return false;
	}

	return !UGTEditorUtilityLibrary::IsPathIgnoredByValidation(InAssetData.PackagePath.ToString());
}

EDataValidationResult UGTEditorValidator::ValidateLoadedAsset_Implementation(const FAssetData& InAssetData,
	UObject* InAsset, FDataValidationContext& InContext)
{
	const FString ExpectedPrefix = UGTEditorUtilityLibrary::GetExpectedPrefixForAsset(InAssetData);

	if (ExpectedPrefix.IsEmpty())
	{
		// No convention configured for this class. Passing is correct; staying silent is not,
		// because an unvalidated asset reads as "not checked" in the results panel.
		AssetPasses(InAsset);
		return EDataValidationResult::Valid;
	}

	const FString AssetName = InAssetData.AssetName.ToString();

	if (!AssetName.StartsWith(ExpectedPrefix))
	{
		AssetFails(InAsset, FText::Format(
			LOCTEXT("BadPrefix", "'{0}' should start with '{1}' for its class ({2})."),
			FText::FromString(AssetName),
			FText::FromString(ExpectedPrefix),
			FText::FromString(InAssetData.AssetClassPath.GetAssetName().ToString())));

		return EDataValidationResult::Invalid;
	}

	AssetPasses(InAsset);

	return EDataValidationResult::Valid;
}

#undef LOCTEXT_NAMESPACE
