// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Engine/GameViewportClient.h"

#include "GTGameViewportClient.generated.h"

/**
 * Project viewport client.
 *
 * Wired up via [/Script/Engine.Engine] GameViewportClientClassName=. Owns the bridge between the
 * OS window and the game: raw input arrival, focus changes, cursor policy and the Slate widget
 * stack drawn over the scene. Split screen layout decisions also land here.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:

	/* UGameViewportClient interface. */
	virtual void Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice = true) override;
	virtual void DetachViewportClient() override;
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	virtual void ReceivedFocus(FViewport* InViewport) override;
	virtual void LostFocus(FViewport* InViewport) override;
	/* UGameViewportClient interface. */

	/** True while the game window holds OS focus. Useful for pausing on focus loss. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Viewport")
	bool HasWindowFocus() const { return bHasWindowFocus; }

private:

	/** Tracks OS focus so gameplay can react without polling the platform layer. */
	bool bHasWindowFocus = true;
};
