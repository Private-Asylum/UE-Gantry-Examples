// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/GameMode/GTGameSession.h"

#include "GantryExamplesLogCategories.h"

AGTGameSession::AGTGameSession()
{
}

void AGTGameSession::InitOptions(const FString& Options)
{
	Super::InitOptions(Options);

	UE_LOG(LogGTNet, Log, TEXT("Game session options: %s"), *Options);
}

FString AGTGameSession::ApproveLogin(const FString& Options)
{
	// Return a non-empty string to reject the connection; the text is shown to the player.
	return Super::ApproveLogin(Options);
}

bool AGTGameSession::AtCapacity(bool bSpectator)
{
	return Super::AtCapacity(bSpectator);
}

void AGTGameSession::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AGTGameSession::NotifyLogout(const APlayerController* PC)
{
	Super::NotifyLogout(PC);
}

void AGTGameSession::RegisterServer()
{
	Super::RegisterServer();
}
