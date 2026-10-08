// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "GameFramework/GameUserSettings.h"

#include "GTGameUserSettings.generated.h"

/**
 * Per-machine, player-facing settings: resolution, quality, audio volumes, accessibility.
 *
 * Wired up via [/Script/Engine.Engine] GameUserSettingsClassName=. Saved to
 * Saved/Config/<Platform>/GameUserSettings.ini, so this is user state, not project configuration.
 * Design tunables belong in UGTDeveloperSettings instead.
 */
UCLASS(Config = GameUserSettings, ConfigDoNotCheckDefaults)
class GANTRYEXAMPLES_API UGTGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UGTGameUserSettings();

	/* UGameUserSettings interface. */
	virtual void SetToDefaults() override;
	virtual void ApplyNonResolutionSettings() override;
	virtual void ValidateSettings() override;
	/* UGameUserSettings interface. */

	/** Typed accessor. Returns nullptr before the engine has created the settings object. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings", meta = (DisplayName = "Get GantryExamples User Settings"))
	static UGTGameUserSettings* Get();

	// ==================================================
	// Audio
	// ==================================================

	/** Master output volume, 0 to 1. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Settings|Audio")
	void SetMasterVolume(float InVolume);

	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings|Audio")
	float GetMasterVolume() const { return MasterVolume; }

	/** Music bus volume, 0 to 1. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Settings|Audio")
	void SetMusicVolume(float InVolume);

	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings|Audio")
	float GetMusicVolume() const { return MusicVolume; }

	/** Sound effects bus volume, 0 to 1. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Settings|Audio")
	void SetSoundEffectsVolume(float InVolume);

	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings|Audio")
	float GetSoundEffectsVolume() const { return SoundEffectsVolume; }

	// ==================================================
	// Gameplay
	// ==================================================

	/** Horizontal look sensitivity multiplier applied on top of the input config. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Settings|Gameplay")
	void SetLookSensitivity(float InSensitivity);

	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings|Gameplay")
	float GetLookSensitivity() const { return LookSensitivity; }

	/** Inverts the vertical look axis. */
	UFUNCTION(BlueprintCallable, Category = "GantryExamples|Settings|Gameplay")
	void SetInvertLookY(bool bInInvert);

	UFUNCTION(BlueprintPure, Category = "GantryExamples|Settings|Gameplay")
	bool GetInvertLookY() const { return bInvertLookY; }

private:

	UPROPERTY(Config)
	float MasterVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SoundEffectsVolume;

	UPROPERTY(Config)
	float LookSensitivity;

	UPROPERTY(Config)
	bool bInvertLookY;
};
