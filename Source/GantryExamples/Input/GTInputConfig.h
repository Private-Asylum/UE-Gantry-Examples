// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Input/GTInput.h"

#include "Engine/DataAsset.h"

#include "GTInputConfig.generated.h"

class UEnhancedInputLocalPlayerSubsystem;

/**
 * Data asset mapping gameplay tags to Enhanced Input actions, plus the contexts to push.
 *
 * Player controllers and pawns hold a reference to one of these and bind by tag. Reassigning
 * which UInputAction a tag points at is then a data change, not a code change.
 */
UCLASS(BlueprintType, Const, meta = (DisplayName = "GantryExamples Input Config"))
class GANTRYEXAMPLES_API UGTInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UGTInputConfig();

	/**
	 * Finds the action bound to a tag.
	 *
	 * @param InputTag The tag to resolve, e.g. GTGameplayTags::Input_Jump.
	 * @param bLogNotFound Log a warning when the tag has no row. Leave true unless the miss is expected.
	 * @return The action, or nullptr when the tag is not mapped.
	 */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Input")
	const UInputAction* FindActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	/** Pushes every mapping context in this config onto the given subsystem. Null-safe. */
	void ApplyMappingContexts(UEnhancedInputLocalPlayerSubsystem* Subsystem) const;

	/** Removes every mapping context in this config from the given subsystem. Null-safe. */
	void RemoveMappingContexts(UEnhancedInputLocalPlayerSubsystem* Subsystem) const;

#if WITH_EDITOR
	/* UObject interface. */
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
	/* UObject interface. */
#endif

	/** Tag-to-action rows. Duplicated tags are reported by IsDataValid. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (TitleProperty = "InputTag"))
	TArray<FGTTaggedInputAction> TaggedActions;

	/** Contexts pushed when this config is applied to a local player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FGTInputMappingContextEntry> MappingContexts;
};
