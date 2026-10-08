// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"

#include "GTUI.generated.h"

/**
 * Category root for UI.
 *
 * Widgets are addressed by layer tag rather than by z-order integers scattered across the code
 * base. A layer decides what can appear above what, and whether it takes input focus, which is
 * the thing that actually goes wrong when UI is stacked by hand.
 */

/** Input policy a layer applies while it has any widget on it. */
UENUM(BlueprintType)
enum class EGTUIInputPolicy : uint8
{
	/** Gameplay keeps input; the layer is purely visual. */
	GameOnly	UMETA(DisplayName = "Game Only"),

	/** Both UI and gameplay receive input. */
	GameAndMenu	UMETA(DisplayName = "Game And Menu"),

	/** UI takes all input and shows the cursor. */
	MenuOnly	UMETA(DisplayName = "Menu Only")
};

/** Describes one HUD layer. Configured on AGTHUD. */
USTRUCT(BlueprintType)
struct GANTRYEXAMPLES_API FGTHUDLayer
{
	GENERATED_BODY()

	/** Identifying tag, e.g. UI.Layer.Menu. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (Categories = "UI.Layer"))
	FGameplayTag LayerTag;

	/** Z-order widgets on this layer are added at. Higher draws on top. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	int32 ZOrder = 0;

	/** Input policy applied while this layer holds a widget. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	EGTUIInputPolicy InputPolicy = EGTUIInputPolicy::GameOnly;
};
