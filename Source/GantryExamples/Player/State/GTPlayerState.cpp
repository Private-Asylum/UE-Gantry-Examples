// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Player/State/GTPlayerState.h"

#include "GantryExamplesLogCategories.h"

#include "Net/UnrealNetwork.h"

AGTPlayerState::AGTPlayerState()
	: TeamIndex(0)
{
	// Player states replicate frequently enough that a slower net update rate is worth it.
	SetNetUpdateFrequency(10.0f);
}

void AGTPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGTPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGTPlayerState, TeamIndex);
}

void AGTPlayerState::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);
}

void AGTPlayerState::CopyProperties(APlayerState* PlayerState)
{
	// Called on the server during seamless travel and on respawn. Anything that should survive
	// a travel must be copied across here, or it is silently lost.
	Super::CopyProperties(PlayerState);

	if (AGTPlayerState* GTPlayerState = Cast<AGTPlayerState>(PlayerState))
	{
		GTPlayerState->TeamIndex = TeamIndex;
	}
}

void AGTPlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);

	if (const AGTPlayerState* GTPlayerState = Cast<AGTPlayerState>(PlayerState))
	{
		TeamIndex = GTPlayerState->TeamIndex;
	}
}

void AGTPlayerState::OnDeactivated()
{
	Super::OnDeactivated();
}

void AGTPlayerState::OnReactivated()
{
	Super::OnReactivated();
}

void AGTPlayerState::SetTeamIndex(uint8 NewTeamIndex)
{
	if (!HasAuthority())
	{
		UE_LOG(LogGTPlayer, Warning, TEXT("SetTeamIndex called without authority on %s."), *GetName());
		return;
	}

	if (TeamIndex == NewTeamIndex)
	{
		return;
	}

	const uint8 OldTeamIndex = TeamIndex;
	TeamIndex = NewTeamIndex;

	// OnRep does not run on the server, so drive it manually to keep both paths identical.
	OnRep_TeamIndex(OldTeamIndex);
}

void AGTPlayerState::OnRep_TeamIndex(uint8 OldTeamIndex)
{
	UE_LOG(LogGTPlayer, Verbose, TEXT("%s team changed: %d -> %d"), *GetPlayerName(), OldTeamIndex, TeamIndex);
}
