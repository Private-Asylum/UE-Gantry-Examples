// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Input/GTInputConfig.h"

#include "GantryExamplesLogCategories.h"

#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#define LOCTEXT_NAMESPACE "GTInputConfig"

UGTInputConfig::UGTInputConfig()
{
}

const UInputAction* UGTInputConfig::FindActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FGTTaggedInputAction& Row : TaggedActions)
	{
		if (Row.InputTag == InputTag && Row.InputAction)
		{
			return Row.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogGTInput, Warning, TEXT("No input action mapped to tag %s in %s."),
			*InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

void UGTInputConfig::ApplyMappingContexts(UEnhancedInputLocalPlayerSubsystem* Subsystem) const
{
	if (!Subsystem)
	{
		return;
	}

	for (const FGTInputMappingContextEntry& Entry : MappingContexts)
	{
		if (Entry.MappingContext)
		{
			Subsystem->AddMappingContext(Entry.MappingContext, static_cast<int32>(Entry.Priority));
		}
	}
}

void UGTInputConfig::RemoveMappingContexts(UEnhancedInputLocalPlayerSubsystem* Subsystem) const
{
	if (!Subsystem)
	{
		return;
	}

	for (const FGTInputMappingContextEntry& Entry : MappingContexts)
	{
		if (Entry.MappingContext)
		{
			Subsystem->RemoveMappingContext(Entry.MappingContext);
		}
	}
}

#if WITH_EDITOR

EDataValidationResult UGTInputConfig::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	TSet<FGameplayTag> SeenTags;

	for (int32 Index = 0; Index < TaggedActions.Num(); ++Index)
	{
		const FGTTaggedInputAction& Row = TaggedActions[Index];

		if (!Row.InputTag.IsValid())
		{
			Context.AddError(FText::Format(LOCTEXT("MissingTag", "Row {0} has no input tag."), Index));
			Result = EDataValidationResult::Invalid;
			continue;
		}

		if (!Row.InputAction)
		{
			Context.AddError(FText::Format(
				LOCTEXT("MissingAction", "Row {0} ({1}) has no input action."),
				Index, FText::FromString(Row.InputTag.ToString())));
			Result = EDataValidationResult::Invalid;
			continue;
		}

		bool bAlreadySeen = false;
		SeenTags.Add(Row.InputTag, &bAlreadySeen);

		if (bAlreadySeen)
		{
			Context.AddError(FText::Format(
				LOCTEXT("DuplicateTag", "Input tag {0} is mapped more than once. The first row wins."),
				FText::FromString(Row.InputTag.ToString())));
			Result = EDataValidationResult::Invalid;
		}
	}

	return Result;
}

#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
