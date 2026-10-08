// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"

#include "GTInput.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * Category root for Input.
 *
 * The project addresses input actions by gameplay tag rather than by hard asset reference, so
 * gameplay code says "bind Input.Jump" and the data asset decides which UInputAction that is.
 * That keeps C++ free of asset pointers and lets designers reassign actions without a recompile.
 */

/**
 * Suggested priorities for mapping contexts. Higher values win conflicts, so a modal menu
 * beats gameplay, and a debug overlay beats everything.
 */
UENUM(BlueprintType)
enum class EGTInputContextPriority : uint8
{
	Gameplay	= 0		UMETA(DisplayName = "Gameplay"),
	Vehicle		= 10	UMETA(DisplayName = "Vehicle"),
	Menu		= 20	UMETA(DisplayName = "Menu"),
	Modal		= 30	UMETA(DisplayName = "Modal"),
	Debug		= 100	UMETA(DisplayName = "Debug")
};

/** One tag-to-action mapping row inside a UGTInputConfig. */
USTRUCT(BlueprintType)
struct GANTRYEXAMPLES_API FGTTaggedInputAction
{
	GENERATED_BODY()

	/** Gameplay tag gameplay code uses to look this action up, e.g. Input.Jump. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (Categories = "Input"))
	FGameplayTag InputTag;

	/** The Enhanced Input action this tag resolves to. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<const UInputAction> InputAction = nullptr;

	/** True when both halves are set and the row is usable. */
	bool IsValid() const { return InputTag.IsValid() && InputAction != nullptr; }
};

/** A mapping context plus the priority it should be pushed at. */
USTRUCT(BlueprintType)
struct GANTRYEXAMPLES_API FGTInputMappingContextEntry
{
	GENERATED_BODY()

	/** Context asset to push. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;

	/** Priority the context is pushed at. Higher wins. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	EGTInputContextPriority Priority = EGTInputContextPriority::Gameplay;
};
