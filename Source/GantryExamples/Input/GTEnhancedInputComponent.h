// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Input/GTInputConfig.h"

#include "EnhancedInputComponent.h"

#include "GTEnhancedInputComponent.generated.h"

/**
 * Input component that can bind by gameplay tag instead of by hard action reference.
 *
 * Set as the project's default via [/Script/Engine.InputSettings] DefaultInputComponentClass in
 * DefaultInput.ini, so both player controllers and pawns get it without any per-class wiring.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	/**
	 * Binds a handler to the action mapped to InputTag in the given config.
	 *
	 * @return The binding handle, or 0 when the tag is not mapped.
	 */
	template <typename UserClass, typename FuncType>
	uint32 BindActionByTag(const UGTInputConfig* InputConfig, const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogNotFound = true);

	/** Removes every binding made through this component. */
	void RemoveAllBindings();
};

template <typename UserClass, typename FuncType>
uint32 UGTEnhancedInputComponent::BindActionByTag(const UGTInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogNotFound)
{
	if (!InputConfig)
	{
		return 0;
	}

	if (const UInputAction* Action = InputConfig->FindActionForTag(InputTag, bLogNotFound))
	{
		return BindAction(Action, TriggerEvent, Object, Func).GetHandle();
	}

	return 0;
}
