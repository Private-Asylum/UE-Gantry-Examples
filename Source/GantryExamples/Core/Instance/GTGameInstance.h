// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Core/GTCore.h"

#include "Engine/GameInstance.h"

#include "GTGameInstance.generated.h"

class UGTSaveSubsystem;

/**
 * Game instance: one per running game, spanning every map load and every world.
 *
 * This is the spine of the project's session lifetime. It owns the lifecycle phase that the rest
 * of the game reads to know whether it is booting, in the front end, or in gameplay, and it is the
 * outer for every UGTGameInstanceSubsystem.
 *
 * Wired up via [/Script/EngineSettings.GameMapsSettings] GameInstanceClass= in DefaultEngine.ini.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UGTGameInstance();

	/* UGameInstance interface. */
	virtual void Init() override;
	virtual void OnStart() override;
	virtual void Shutdown() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void StartGameInstance() override;
	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;
	virtual void ReturnToMainMenu() override;
	/* UGameInstance interface. */

	// ==================================================
	// Lifecycle
	// ==================================================

	/** Current coarse lifecycle phase. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Lifecycle")
	EGTGameLifecyclePhase GetLifecyclePhase() const { return LifecyclePhase; }

	/**
	 * Moves the instance to a new lifecycle phase and notifies listeners.
	 * A no-op if the phase is unchanged.
	 */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Lifecycle")
	void SetLifecyclePhase(EGTGameLifecyclePhase NewPhase);

	/** Fired after the phase has changed. Blueprint friendly. */
	UPROPERTY(BlueprintAssignable, Category = "GantryExamples|Lifecycle")
	FGTOnGameLifecyclePhaseChanged OnLifecyclePhaseChanged;

	/** Native counterpart of OnLifecyclePhaseChanged. */
	FGTOnGameLifecyclePhaseChangedNative OnLifecyclePhaseChangedNative;

	// ==================================================
	// Convenience
	// ==================================================

	/** Typed accessor from any object with a world. Returns nullptr outside of a game world. */
	static UGTGameInstance* Get(const UObject* WorldContextObject);

private:

	/** Backing store for GetLifecyclePhase. */
	UPROPERTY(Transient)
	EGTGameLifecyclePhase LifecyclePhase;
};
