// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/GameSession.h"

#include "GTGameSession.generated.h"

/**
 * Server-side gatekeeper for a hosted match.
 *
 * Spawned by the game mode and existing only on the server. It answers the questions the game mode
 * should not have to: is this server full, is this player allowed in, should they be kicked or
 * banned. Keeping that separate means admission policy can change without touching match rules.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTGameSession : public AGameSession
{
	GENERATED_BODY()

public:

	AGTGameSession();

	/* AGameSession interface. */
	virtual void InitOptions(const FString& Options) override;
	virtual FString ApproveLogin(const FString& Options) override;
	virtual bool AtCapacity(bool bSpectator) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void NotifyLogout(const APlayerController* PC) override;
	virtual void RegisterServer() override;
	/* AGameSession interface. */
};
