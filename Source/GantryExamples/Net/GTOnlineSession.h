// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/OnlineSession.h"

#include "GTOnlineSession.generated.h"

/**
 * Client-side online session handling, owned by the game instance.
 *
 * The bridge between the online subsystem and the game: invites accepted from the platform UI,
 * session join and leave, and what to do when the connection drops. Kept separate from
 * UGTGameInstance so platform-specific behaviour has somewhere to live that is not the spine of
 * the game.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTOnlineSession : public UOnlineSession
{
	GENERATED_BODY()

public:

	/* UOnlineSession interface. */
	virtual void RegisterOnlineDelegates() override;
	virtual void ClearOnlineDelegates() override;
	virtual void HandleDisconnect(UWorld* World, UNetDriver* NetDriver) override;
	virtual void StartOnlineSession(FName SessionName) override;
	virtual void EndOnlineSession(FName SessionName) override;
	/* UOnlineSession interface. */
};
