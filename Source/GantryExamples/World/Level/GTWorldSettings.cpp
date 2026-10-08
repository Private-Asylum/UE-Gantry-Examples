// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/Level/GTWorldSettings.h"

#include "GantryExamplesLogCategories.h"
#include "Net/GTGameNetworkManager.h"

AGTWorldSettings::AGTWorldSettings()
	: bIsFrontEndMap(false)
{
	// The world spawns this class as its network manager during BeginPlay on the server.
	GameNetworkManagerClass = AGTGameNetworkManager::StaticClass();
}

void AGTWorldSettings::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

#if WITH_EDITOR

void AGTWorldSettings::CheckForErrors()
{
	Super::CheckForErrors();

	// Map validation lives here so it shows up in the editor's Map Check results. The editor
	// module's validator covers assets; this covers levels.
}

#endif // WITH_EDITOR
