// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "AssetRegistry/AssetData.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GTEditorUtilityLibrary.generated.h"

/**
 * Editor-only Blueprint helpers, callable from Editor Utility Widgets and Blutilities.
 *
 * Everything here runs in the editor process only and is compiled out of runtime targets. If a
 * function needs to exist at runtime it belongs in the GantryExamples module, not here.
 */
UCLASS()
class UGTEditorUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Returns every asset under a content path.
	 *
	 * @param PackagePath Content path to scan, e.g. "/Game/Characters".
	 * @param bRecursive Include subfolders.
	 */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Editor")
	static TArray<FAssetData> GetAssetsInPath(const FString& PackagePath, bool bRecursive = true);

	/**
	 * Reports assets whose names do not match the prefix configured for their class.
	 * Prefixes come from UGTEditorSettings.
	 *
	 * @return Human readable descriptions of each violation, empty when everything conforms.
	 */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Editor")
	static TArray<FString> FindAssetNamingViolations(const FString& PackagePath);

	/** Returns the expected name prefix for an asset's class, or an empty string when unconfigured. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Editor")
	static FString GetExpectedPrefixForAsset(const FAssetData& AssetData);

	/** True when the path is excluded from validation by UGTEditorSettings. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Editor")
	static bool IsPathIgnoredByValidation(const FString& PackagePath);
};
