// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Player/GTPlayer.h"

#include "GameFramework/PlayerState.h"

#include "GTPlayerState.generated.h"

/**
 * Replicated per-player state, visible to every machine.
 *
 * Survives pawn death and seamless travel, which makes it the correct owner of anything that
 * should outlive the body: score, team, loadout selection, persistent per-match stats.
 *
 * Anything here is replicated to all clients, so do not put secrets on it.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AGTPlayerState();

	/* AActor interface. */
	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/* AActor interface. */

	/* APlayerState interface. */
	virtual void ClientInitialize(AController* C) override;
	virtual void OnDeactivated() override;
	virtual void OnReactivated() override;
	/* APlayerState interface. */

	/** Team this player belongs to. Index 0 means unassigned. */
	UPROPERTY(ReplicatedUsing = OnRep_TeamIndex, BlueprintReadOnly, Category = "GantryExamples|Player")
	uint8 TeamIndex;

	/** Server-side setter for TeamIndex. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Player")
	void SetTeamIndex(uint8 NewTeamIndex);

protected:

	/* APlayerState interface. Both are protected in the base class. */
	virtual void CopyProperties(APlayerState* PlayerState) override;
	virtual void OverrideWith(APlayerState* PlayerState) override;
	/* APlayerState interface. */

	/** Replication callback for TeamIndex. */
	UFUNCTION()
	virtual void OnRep_TeamIndex(uint8 OldTeamIndex);
};
