// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Camera/PlayerCameraManager.h"

#include "GTPlayerCameraManager.generated.h"

/**
 * Per-player camera manager: the final say on what the player sees.
 *
 * Spawned by AGTPlayerController. Every camera component, spring arm and view target feeds into
 * this class, which blends them, applies camera modifiers and post process, and hands the result
 * to the renderer. If the view is wrong and the camera component looks right, the answer is here.
 */
UCLASS()
class GANTRYEXAMPLES_API AGTPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	AGTPlayerCameraManager();

	/* APlayerCameraManager interface. */
	virtual void InitializeFor(APlayerController* PC) override;
	virtual void ApplyCameraModifiers(float DeltaTime, FMinimalViewInfo& InOutPOV) override;
	virtual void ProcessViewRotation(float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;
	/* APlayerCameraManager interface. */

protected:

	/* APlayerCameraManager interface. */
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
	/* APlayerCameraManager interface. */

	/** Default field of view applied on initialisation. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GantryExamples|Camera", meta = (ClampMin = "5.0", ClampMax = "170.0"))
	float DefaultFieldOfView;
};
