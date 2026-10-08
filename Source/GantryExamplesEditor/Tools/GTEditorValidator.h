// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "EditorValidatorBase.h"

#include "GTEditorValidator.generated.h"

/**
 * Asset validator enforcing the project's naming conventions.
 *
 * Discovered automatically by the Data Validation plugin, so it runs on Validate Data, on save
 * when enabled, and in commandlet form on CI. Rules come from UGTEditorSettings so they can be
 * tuned without a recompile.
 *
 * Add further validators as siblings rather than extending this one; one validator per rule keeps
 * failures legible in the results panel.
 */
UCLASS()
class UGTEditorValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

public:

	UGTEditorValidator();

protected:

	/* UEditorValidatorBase interface. */
	virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InObject, FDataValidationContext& InContext) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;
	/* UEditorValidatorBase interface. */
};
