// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/GameStateBase.h"

#include "GTGameStateBase.generated.h"

/**
 * Replicated, world-scoped state that every client is allowed to know.
 *
 * The game mode decides; the game state publishes. If a client needs a fact about the match,
 * it lives here, not on the game mode. Pairs with AGTGameModeBase.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:

	AGTGameStateBase();

	/* AGameStateBase interface. */
	virtual void PostInitializeComponents() override;
	virtual void HandleBeginPlay() override;
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/* AGameStateBase interface. */

	/** Fired on every machine when a player state joins or leaves the game state's list. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FGTOnPlayerStateSetChanged, APlayerState* /*PlayerState*/);

	/** Broadcast after a player state has been added to PlayerArray. */
	FGTOnPlayerStateSetChanged OnPlayerStateAdded;

	/** Broadcast after a player state has been removed from PlayerArray. */
	FGTOnPlayerStateSetChanged OnPlayerStateRemoved;
};
