// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Instance/GTGameInstanceSubsystem.h"

#include "GantryExamplesLogCategories.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"

bool UGTGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	// Abstract bases must never be instantiated by the collection.
	if (GetClass()->HasAnyClassFlags(CLASS_Abstract))
	{
		return false;
	}

	if (!ShouldCreateOnDedicatedServer())
	{
		if (const UGameInstance* GameInstance = Cast<UGameInstance>(Outer))
		{
			if (const UWorld* World = GameInstance->GetWorld())
			{
				if (World->GetNetMode() == NM_DedicatedServer)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void UGTGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogGTCore, Verbose, TEXT("%s initialised."), *GetClass()->GetName());
}

void UGTGameInstanceSubsystem::Deinitialize()
{
	UE_LOG(LogGTCore, Verbose, TEXT("%s deinitialised."), *GetClass()->GetName());

	Super::Deinitialize();
}
