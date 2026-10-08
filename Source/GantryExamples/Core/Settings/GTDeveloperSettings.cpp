// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Settings/GTDeveloperSettings.h"

#include "GantryExamplesLogCategories.h"

#define LOCTEXT_NAMESPACE "GTDeveloperSettings"

UGTDeveloperSettings::UGTDeveloperSettings()
	: BuildId(TEXT("local"))
	, BuildEnvironment(EGTBuildEnvironment::Development)
	, SaveGameClass(TEXT("/Script/GantryExamples.GTSaveGame"))
	, AutosaveIntervalSeconds(300.0f)
	, bShowDebugHUDByDefault(false)
{
	CategoryName = TEXT("Game");
	SectionName = TEXT("GantryExamples");
}

bool UGTDeveloperSettings::AllowsCheats() const
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return BuildEnvironment != EGTBuildEnvironment::Live;
#endif
}

FString UGTDeveloperSettings::ToDebugString() const
{
	const UEnum* EnvironmentEnum = StaticEnum<EGTBuildEnvironment>();

	return FString::Printf(
		TEXT("GantryExamples settings:\n")
		TEXT("  BuildId                 : %s\n")
		TEXT("  BuildEnvironment        : %s\n")
		TEXT("  FrontEndMap             : %s\n")
		TEXT("  DefaultInputContexts    : %d\n")
		TEXT("  SaveGameClass           : %s\n")
		TEXT("  AutosaveIntervalSeconds : %.1f\n")
		TEXT("  ShowDebugHUDByDefault   : %s\n")
		TEXT("  AllowsCheats            : %s"),
		*BuildId,
		EnvironmentEnum ? *EnvironmentEnum->GetNameStringByValue(static_cast<int64>(BuildEnvironment)) : TEXT("<unknown>"),
		*FrontEndMap.ToString(),
		DefaultInputMappingContexts.Num(),
		*SaveGameClass.ToString(),
		AutosaveIntervalSeconds,
		bShowDebugHUDByDefault ? TEXT("true") : TEXT("false"),
		AllowsCheats() ? TEXT("true") : TEXT("false"));
}

#if WITH_EDITOR

FText UGTDeveloperSettings::GetSectionText() const
{
	return LOCTEXT("SectionText", "GantryExamples");
}

FText UGTDeveloperSettings::GetSectionDescription() const
{
	return LOCTEXT("SectionDescription", "Project wide gameplay, bootstrap and diagnostic settings for GantryExamples.");
}

void UGTDeveloperSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.GetPropertyName();

	UE_LOG(LogGTCore, Verbose, TEXT("GantryExamples setting changed: %s"), *PropertyName.ToString());
}

#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
