// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Player/Camera/GTPlayerCameraManager.h"

#include "Core/Settings/GTGameUserSettings.h"
#include "GantryExamplesLogCategories.h"

AGTPlayerCameraManager::AGTPlayerCameraManager()
	: DefaultFieldOfView(90.0f)
{
	// Clamp pitch so the player cannot look through their own body.
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
}

void AGTPlayerCameraManager::InitializeFor(APlayerController* PC)
{
	Super::InitializeFor(PC);

	SetFOV(DefaultFieldOfView);
}

void AGTPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);
}

void AGTPlayerCameraManager::ApplyCameraModifiers(float DeltaTime, FMinimalViewInfo& InOutPOV)
{
	Super::ApplyCameraModifiers(DeltaTime, InOutPOV);
}

void AGTPlayerCameraManager::ProcessViewRotation(float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot)
{
	// User sensitivity and invert are applied here, where they affect every input device at once
	// rather than being duplicated into each look binding.
	if (const UGTGameUserSettings* Settings = UGTGameUserSettings::Get())
	{
		OutDeltaRot.Yaw *= Settings->GetLookSensitivity();
		OutDeltaRot.Pitch *= Settings->GetLookSensitivity() * (Settings->GetInvertLookY() ? -1.0f : 1.0f);
	}

	Super::ProcessViewRotation(DeltaTime, OutViewRotation, OutDeltaRot);
}
