// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "EditorSubsystem.h"

#include "GTEditorSubsystem.generated.h"

/**
 * Editor-scope subsystem: one instance for the editor process, created after the editor engine
 * is up and destroyed on exit.
 *
 * The right home for tooling that needs a UObject lifetime and engine delegates: reacting to asset
 * saves, map loads or PIE start and stop. Slate UI registration belongs in the module instead.
 */
UCLASS()
class UGTEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:

	/* USubsystem interface. */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* USubsystem interface. */

	/** Typed accessor. Returns nullptr outside the editor. */
	static UGTEditorSubsystem* Get();

private:

	/** Called when a PIE session begins. */
	void HandlePieBegun(bool bIsSimulating);

	/** Called when a PIE session ends. */
	void HandlePieEnded(bool bIsSimulating);

	/** Called after any package is saved, used to drive validate-on-save. */
	void HandlePackageSaved(const FString& PackageFileName, UPackage* Package, FObjectPostSaveContext Context);

	FDelegateHandle PieBegunHandle;
	FDelegateHandle PieEndedHandle;
	FDelegateHandle PackageSavedHandle;
};
