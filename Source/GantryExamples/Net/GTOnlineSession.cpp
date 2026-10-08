// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Net/GTOnlineSession.h"

#include "GantryExamplesLogCategories.h"

void UGTOnlineSession::RegisterOnlineDelegates()
{
	Super::RegisterOnlineDelegates();
}

void UGTOnlineSession::ClearOnlineDelegates()
{
	Super::ClearOnlineDelegates();
}

void UGTOnlineSession::HandleDisconnect(UWorld* World, UNetDriver* NetDriver)
{
	UE_LOG(LogGTNet, Warning, TEXT("Disconnected from session."));

	Super::HandleDisconnect(World, NetDriver);
}

void UGTOnlineSession::StartOnlineSession(FName SessionName)
{
	Super::StartOnlineSession(SessionName);
}

void UGTOnlineSession::EndOnlineSession(FName SessionName)
{
	Super::EndOnlineSession(SessionName);
}
