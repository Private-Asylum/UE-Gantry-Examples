// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Instance/GTGameInstance.h"

#include "GantryExamplesLogCategories.h"
#include "Net/GTOnlineSession.h"

#include "Engine/Engine.h"
#include "Engine/World.h"

UGTGameInstance::UGTGameInstance()
	: LifecyclePhase(EGTGameLifecyclePhase::None)
{
}

UGTGameInstance* UGTGameInstance::Get(const UObject* WorldContextObject)
{
	if (!GEngine || !WorldContextObject)
	{
		return nullptr;
	}

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	return World ? Cast<UGTGameInstance>(World->GetGameInstance()) : nullptr;
}

void UGTGameInstance::Init()
{
	Super::Init();

	SetLifecyclePhase(EGTGameLifecyclePhase::Initialising);

	UE_LOG(LogGTCore, Log, TEXT("GTGameInstance initialised."));
}

void UGTGameInstance::OnStart()
{
	Super::OnStart();

	UE_LOG(LogGTCore, Log, TEXT("GTGameInstance started."));
}

void UGTGameInstance::Shutdown()
{
	SetLifecyclePhase(EGTGameLifecyclePhase::ShuttingDown);

	UE_LOG(LogGTCore, Log, TEXT("GTGameInstance shutting down."));

	Super::Shutdown();
}

void UGTGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

void UGTGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	UE_LOG(LogGTCore, Verbose, TEXT("World changed: %s -> %s"),
		OldWorld ? *OldWorld->GetName() : TEXT("<none>"),
		NewWorld ? *NewWorld->GetName() : TEXT("<none>"));
}

TSubclassOf<UOnlineSession> UGTGameInstance::GetOnlineSessionClass()
{
	return UGTOnlineSession::StaticClass();
}

void UGTGameInstance::ReturnToMainMenu()
{
	SetLifecyclePhase(EGTGameLifecyclePhase::Loading);

	Super::ReturnToMainMenu();
}

void UGTGameInstance::SetLifecyclePhase(EGTGameLifecyclePhase NewPhase)
{
	if (NewPhase == LifecyclePhase)
	{
		return;
	}

	const EGTGameLifecyclePhase OldPhase = LifecyclePhase;
	LifecyclePhase = NewPhase;

	if (const UEnum* PhaseEnum = StaticEnum<EGTGameLifecyclePhase>())
	{
		UE_LOG(LogGTCore, Log, TEXT("Lifecycle phase: %s -> %s"),
			*PhaseEnum->GetNameStringByValue(static_cast<int64>(OldPhase)),
			*PhaseEnum->GetNameStringByValue(static_cast<int64>(NewPhase)));
	}

	OnLifecyclePhaseChanged.Broadcast(OldPhase, NewPhase);
	OnLifecyclePhaseChangedNative.Broadcast(OldPhase, NewPhase);
}
