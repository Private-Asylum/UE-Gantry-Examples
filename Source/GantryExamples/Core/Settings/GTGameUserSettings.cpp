// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Settings/GTGameUserSettings.h"

#include "GantryExamplesLogCategories.h"

#include "Engine/Engine.h"

UGTGameUserSettings::UGTGameUserSettings()
{
	// The engine calls SetToDefaults itself, but a fresh CDO should still be sane.
	UGTGameUserSettings::SetToDefaults();
}

UGTGameUserSettings* UGTGameUserSettings::Get()
{
	return GEngine ? Cast<UGTGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

void UGTGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	MasterVolume = 1.0f;
	MusicVolume = 0.8f;
	SoundEffectsVolume = 1.0f;
	LookSensitivity = 1.0f;
	bInvertLookY = false;
}

void UGTGameUserSettings::ValidateSettings()
{
	Super::ValidateSettings();

	MasterVolume = FMath::Clamp(MasterVolume, 0.0f, 1.0f);
	MusicVolume = FMath::Clamp(MusicVolume, 0.0f, 1.0f);
	SoundEffectsVolume = FMath::Clamp(SoundEffectsVolume, 0.0f, 1.0f);
	LookSensitivity = FMath::Clamp(LookSensitivity, 0.01f, 10.0f);
}

void UGTGameUserSettings::ApplyNonResolutionSettings()
{
	Super::ApplyNonResolutionSettings();

	// Push the audio values at your sound class / submix mixes here once they exist.
	UE_LOG(LogGTCore, Verbose, TEXT("Applied user settings. Master %.2f, Music %.2f, SFX %.2f."),
		MasterVolume, MusicVolume, SoundEffectsVolume);
}

void UGTGameUserSettings::SetMasterVolume(float InVolume)
{
	MasterVolume = FMath::Clamp(InVolume, 0.0f, 1.0f);
}

void UGTGameUserSettings::SetMusicVolume(float InVolume)
{
	MusicVolume = FMath::Clamp(InVolume, 0.0f, 1.0f);
}

void UGTGameUserSettings::SetSoundEffectsVolume(float InVolume)
{
	SoundEffectsVolume = FMath::Clamp(InVolume, 0.0f, 1.0f);
}

void UGTGameUserSettings::SetLookSensitivity(float InSensitivity)
{
	LookSensitivity = FMath::Clamp(InSensitivity, 0.01f, 10.0f);
}

void UGTGameUserSettings::SetInvertLookY(bool bInInvert)
{
	bInvertLookY = bInInvert;
}
