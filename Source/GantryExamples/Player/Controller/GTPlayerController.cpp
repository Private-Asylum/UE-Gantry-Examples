// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Player/Controller/GTPlayerController.h"

#include "Core/Settings/GTDeveloperSettings.h"
#include "GantryExamplesLogCategories.h"
#include "Input/GTEnhancedInputComponent.h"
#include "Input/GTInputConfig.h"
#include "Player/Controller/GTCheatManager.h"
#include "Player/Camera/GTPlayerCameraManager.h"
#include "Player/State/GTPlayerState.h"

#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerState.h"
#include "InputMappingContext.h"

AGTPlayerController::AGTPlayerController()
	: ReadyState(EGTPlayerReadyState::Connecting)
	, bBroadcastPlayerStateReady(false)
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraManagerClass = AGTPlayerCameraManager::StaticClass();
	CheatClass = UGTCheatManager::StaticClass();

	// The controller's own input component class comes from
	// [/Script/Engine.InputSettings] DefaultInputComponentClass in DefaultInput.ini,
	// which this project points at UGTEnhancedInputComponent.
}

void AGTPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ApplyDefaultInputMappings();

	// PlayerState may already be valid on the server and in standalone.
	HandlePlayerStateReady();
}

void AGTPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SetReadyState(EGTPlayerReadyState::Leaving);

	Super::EndPlay(EndPlayReason);
}

void AGTPlayerController::InitPlayerState()
{
	Super::InitPlayerState();

	HandlePlayerStateReady();
}

void AGTPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// On clients this is the first point at which PlayerState is safe to read.
	HandlePlayerStateReady();
}

void AGTPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetReadyState(EGTPlayerReadyState::Playing);

	UE_LOG(LogGTPlayer, Verbose, TEXT("%s possessed %s."), *GetName(), *GetNameSafe(InPawn));
}

void AGTPlayerController::OnUnPossess()
{
	if (ReadyState == EGTPlayerReadyState::Playing)
	{
		SetReadyState(EGTPlayerReadyState::Ready);
	}

	Super::OnUnPossess();
}

void AGTPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
}

void AGTPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
}

void AGTPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

	// The Enhanced Input subsystem only exists once a ULocalPlayer is attached.
	ApplyDefaultInputMappings();
}

void AGTPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AGTPlayerController::UpdateRotation(float DeltaTime)
{
	Super::UpdateRotation(DeltaTime);
}

void AGTPlayerController::AddCheats(bool bForce)
{
	const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get();

	// Honour the project's build environment rather than the engine's default policy.
	Super::AddCheats(bForce || (Settings && Settings->AllowsCheats()));
}

void AGTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	BindInputActions();
}

void AGTPlayerController::BindInputActions()
{
	// Bind controller-level actions here (pause, scoreboard, chat). Movement and other
	// body-driven actions belong on the pawn, which binds them on possession.
}

UEnhancedInputLocalPlayerSubsystem* AGTPlayerController::GetEnhancedInputSubsystem() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();

	return LocalPlayer ? LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>() : nullptr;
}

void AGTPlayerController::ApplyDefaultInputMappings()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();

	if (!Subsystem)
	{
		// Not a local player, or the local player is not attached yet. Both are expected.
		return;
	}

	if (const UGTDeveloperSettings* Settings = UGTDeveloperSettings::Get())
	{
		int32 Priority = 0;

		for (const TSoftObjectPtr<UInputMappingContext>& ContextPtr : Settings->DefaultInputMappingContexts)
		{
			if (UInputMappingContext* Context = ContextPtr.LoadSynchronous())
			{
				Subsystem->AddMappingContext(Context, Priority++);
			}
		}
	}

	if (InputConfig)
	{
		InputConfig->ApplyMappingContexts(Subsystem);
	}
}

void AGTPlayerController::AddInputMappingContext(UInputMappingContext* MappingContext, int32 Priority)
{
	if (!MappingContext)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem())
	{
		Subsystem->AddMappingContext(MappingContext, Priority);
	}
}

void AGTPlayerController::RemoveInputMappingContext(UInputMappingContext* MappingContext)
{
	if (!MappingContext)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem())
	{
		Subsystem->RemoveMappingContext(MappingContext);
	}
}

void AGTPlayerController::HandlePlayerStateReady()
{
	if (bBroadcastPlayerStateReady || !PlayerState)
	{
		return;
	}

	bBroadcastPlayerStateReady = true;

	SetReadyState(EGTPlayerReadyState::Ready);

	OnPlayerStateReady.Broadcast(PlayerState);
}

void AGTPlayerController::SetReadyState(EGTPlayerReadyState NewState)
{
	if (NewState == ReadyState)
	{
		return;
	}

	ReadyState = NewState;

	OnReadyStateChanged.Broadcast(PlayerState, NewState);
}
