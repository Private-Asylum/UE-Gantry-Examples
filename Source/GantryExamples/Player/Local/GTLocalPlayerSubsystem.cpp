// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Player/Local/GTLocalPlayerSubsystem.h"

#include "GantryExamplesLogCategories.h"
#include "Player/Local/GTLocalPlayer.h"

bool UGTLocalPlayerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	return !GetClass()->HasAnyClassFlags(CLASS_Abstract);
}

void UGTLocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogGTPlayer, Verbose, TEXT("%s initialised."), *GetClass()->GetName());
}

void UGTLocalPlayerSubsystem::Deinitialize()
{
	UE_LOG(LogGTPlayer, Verbose, TEXT("%s deinitialised."), *GetClass()->GetName());

	Super::Deinitialize();
}

UGTLocalPlayer* UGTLocalPlayerSubsystem::GetGTLocalPlayer() const
{
	return Cast<UGTLocalPlayer>(GetLocalPlayer<ULocalPlayer>());
}
