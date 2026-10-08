// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GTCore.generated.h"

/**
 * Category root for Core.
 *
 * Declares the types shared by the engine-scope, instance-scope and settings classes underneath
 * this folder. Nothing here should know about gameplay; if it needs a UWorld, it belongs in World.
 */

/** Coarse lifecycle phase of the running application, driven by UGTGameInstance. */
UENUM(BlueprintType)
enum class EGTGameLifecyclePhase : uint8
{
	/** Engine is up, game instance has not been initialised yet. */
	None			UMETA(DisplayName = "None"),

	/** UGTGameInstance::Init has run. Subsystems exist, no world is loaded. */
	Initialising	UMETA(DisplayName = "Initialising"),

	/** Front end / main menu map is loaded. */
	FrontEnd		UMETA(DisplayName = "Front End"),

	/** A gameplay map is loading. */
	Loading			UMETA(DisplayName = "Loading"),

	/** A gameplay map is loaded and ticking. */
	InGame			UMETA(DisplayName = "In Game"),

	/** UGTGameInstance::Shutdown has begun. */
	ShuttingDown	UMETA(DisplayName = "Shutting Down")
};

/** Where the running build sits on the shipping ramp. Drives cheat and debug availability. */
UENUM(BlueprintType)
enum class EGTBuildEnvironment : uint8
{
	Development	UMETA(DisplayName = "Development"),
	Playtest	UMETA(DisplayName = "Playtest"),
	Certification UMETA(DisplayName = "Certification"),
	Live		UMETA(DisplayName = "Live")
};

/** Broadcast by UGTGameInstance whenever the lifecycle phase changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGTOnGameLifecyclePhaseChanged, EGTGameLifecyclePhase, OldPhase, EGTGameLifecyclePhase, NewPhase);

/** Native (non-dynamic) counterpart for C++ listeners that want a lambda. */
DECLARE_MULTICAST_DELEGATE_TwoParams(FGTOnGameLifecyclePhaseChangedNative, EGTGameLifecyclePhase /*OldPhase*/, EGTGameLifecyclePhase /*NewPhase*/);

/** Constants that would otherwise be scattered as magic values. */
namespace GTCore
{
	/** Primary asset type used for anything the asset manager should scan up front. */
	static const FName PrimaryAssetType_GameData(TEXT("GTGameData"));

	/** Save slot used when no explicit slot is given. */
	static const TCHAR* DefaultSaveSlotName = TEXT("GTDefault");
}
