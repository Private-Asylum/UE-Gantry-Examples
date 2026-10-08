// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"

#include "GTEditorSettings.generated.h"

/**
 * Per-user editor preferences for the project's tooling.
 *
 * Surfaced under Editor Preferences -> Plugins -> GantryExamplesEditor, and saved to
 * Saved/Config/.../EditorPerProjectUserSettings.ini. Per-user by design: these are workflow
 * preferences, not project policy. Anything the whole team must agree on belongs in
 * UGTDeveloperSettings on the runtime side.
 */
UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "GantryExamplesEditor"))
class UGTEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UGTEditorSettings();

	/* UDeveloperSettings interface. */
	virtual FName GetContainerName() const override { return TEXT("Editor"); }
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
	virtual FName GetSectionName() const override { return TEXT("GantryExamplesEditor"); }
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
	/* UDeveloperSettings interface. */

	/** Settings are a CDO, so this never returns nullptr once the class is loaded. */
	static const UGTEditorSettings* Get() { return GetDefault<UGTEditorSettings>(); }

	/** Runs the project's asset validator when an asset is saved. */
	UPROPERTY(Config, EditAnywhere, Category = "Validation")
	bool bValidateOnSave;

	/** Logs a warning for assets whose names do not match the project's prefix conventions. */
	UPROPERTY(Config, EditAnywhere, Category = "Validation")
	bool bEnforceAssetNamingConventions;

	/**
	 * Expected asset name prefixes, keyed by class name.
	 * For example "Texture2D" -> "T_". An empty map disables prefix checking entirely.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "Validation", meta = (EditCondition = "bEnforceAssetNamingConventions"))
	TMap<FString, FString> AssetNamePrefixesByClass;

	/** Content paths the validator ignores, e.g. "/Game/ThirdParty". */
	UPROPERTY(Config, EditAnywhere, Category = "Validation", meta = (ContentDir))
	TArray<FString> ValidationIgnorePaths;
};
