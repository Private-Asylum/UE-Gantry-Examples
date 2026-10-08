// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Engine/LocalPlayer.h"

#include "GTLocalPlayer.generated.h"

/**
 * One per local human being at the machine, created before any world and outliving every map.
 *
 * Wired up via [/Script/Engine.Engine] LocalPlayerClassName=. Because it survives travel and
 * possession, this is where per-human, per-session state belongs: which profile is signed in,
 * which gamepad is theirs, which settings they picked. Anything world-specific belongs on the
 * player controller instead.
 *
 * It is also the outer for every ULocalPlayerSubsystem, including Enhanced Input's.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:

	UGTLocalPlayer();

	/* ULocalPlayer interface. */
	virtual void PlayerAdded(UGameViewportClient* InViewportClient, FPlatformUserId InUserId) override;
	virtual void PlayerRemoved() override;
	virtual bool SpawnPlayActor(const FString& URL, FString& OutError, UWorld* InWorld) override;
	virtual void ReceivedPlayerController(APlayerController* NewController) override;
	virtual void SetControllerId(int32 NewControllerId) override;
	/* ULocalPlayer interface. */

	/** Fired when this local player gains or loses its player controller. */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FGTOnPlayerControllerChanged, UGTLocalPlayer* /*LocalPlayer*/, APlayerController* /*NewController*/);

	/** Broadcast from ReceivedPlayerController, including on map travel. */
	FGTOnPlayerControllerChanged OnPlayerControllerChanged;
};
