// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Tools/GTEditorSubsystem.h"

#include "GantryExamplesEditorLogCategories.h"
#include "Settings/GTEditorSettings.h"

#include "Editor.h"
#include "UObject/ObjectSaveContext.h"

void UGTEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PieBegunHandle = FEditorDelegates::BeginPIE.AddUObject(this, &UGTEditorSubsystem::HandlePieBegun);
	PieEndedHandle = FEditorDelegates::EndPIE.AddUObject(this, &UGTEditorSubsystem::HandlePieEnded);
	PackageSavedHandle = UPackage::PackageSavedWithContextEvent.AddUObject(this, &UGTEditorSubsystem::HandlePackageSaved);

	UE_LOG(LogGantryExamplesEditor, Log, TEXT("GTEditorSubsystem initialised."));
}

void UGTEditorSubsystem::Deinitialize()
{
	FEditorDelegates::BeginPIE.Remove(PieBegunHandle);
	FEditorDelegates::EndPIE.Remove(PieEndedHandle);
	UPackage::PackageSavedWithContextEvent.Remove(PackageSavedHandle);

	Super::Deinitialize();
}

UGTEditorSubsystem* UGTEditorSubsystem::Get()
{
	return GEditor ? GEditor->GetEditorSubsystem<UGTEditorSubsystem>() : nullptr;
}

void UGTEditorSubsystem::HandlePieBegun(bool bIsSimulating)
{
	UE_LOG(LogGantryExamplesEditor, Verbose, TEXT("PIE begun (simulating: %s)."), bIsSimulating ? TEXT("yes") : TEXT("no"));
}

void UGTEditorSubsystem::HandlePieEnded(bool bIsSimulating)
{
	UE_LOG(LogGantryExamplesEditor, Verbose, TEXT("PIE ended."));
}

void UGTEditorSubsystem::HandlePackageSaved(const FString& PackageFileName, UPackage* Package, FObjectPostSaveContext Context)
{
	const UGTEditorSettings* Settings = UGTEditorSettings::Get();

	if (!Settings || !Settings->bValidateOnSave || Context.IsProceduralSave())
	{
		return;
	}

	UE_LOG(LogGTEditorValidation, Verbose, TEXT("Saved %s."), *PackageFileName);
}
