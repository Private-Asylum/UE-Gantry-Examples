// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Settings/GTEditorSettings.h"

#define LOCTEXT_NAMESPACE "GTEditorSettings"

UGTEditorSettings::UGTEditorSettings()
	: bValidateOnSave(true)
	, bEnforceAssetNamingConventions(true)
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("GantryExamplesEditor");

	// A starting point rather than a mandate. Adjust to whatever the project settles on.
	AssetNamePrefixesByClass.Add(TEXT("Blueprint"),			TEXT("BP_"));
	AssetNamePrefixesByClass.Add(TEXT("WidgetBlueprint"),	TEXT("WBP_"));
	AssetNamePrefixesByClass.Add(TEXT("Texture2D"),			TEXT("T_"));
	AssetNamePrefixesByClass.Add(TEXT("Material"),			TEXT("M_"));
	AssetNamePrefixesByClass.Add(TEXT("MaterialInstanceConstant"), TEXT("MI_"));
	AssetNamePrefixesByClass.Add(TEXT("StaticMesh"),		TEXT("SM_"));
	AssetNamePrefixesByClass.Add(TEXT("SkeletalMesh"),		TEXT("SK_"));
	AssetNamePrefixesByClass.Add(TEXT("AnimSequence"),		TEXT("AS_"));
	AssetNamePrefixesByClass.Add(TEXT("SoundWave"),			TEXT("SW_"));
	AssetNamePrefixesByClass.Add(TEXT("InputAction"),		TEXT("IA_"));
	AssetNamePrefixesByClass.Add(TEXT("InputMappingContext"), TEXT("IMC_"));
}

#if WITH_EDITOR

FText UGTEditorSettings::GetSectionText() const
{
	return LOCTEXT("SectionText", "GantryExamplesEditor");
}

FText UGTEditorSettings::GetSectionDescription() const
{
	return LOCTEXT("SectionDescription", "Per-user preferences for the GantryExamples editor tooling.");
}

#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
