// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"

#include "GTUserWidget.generated.h"

class AGTHUD;
class AGTPlayerController;

/**
 * Base class for every widget Blueprint in the project.
 *
 * Provides typed accessors for the owning controller and HUD so widget graphs stop casting, and
 * a single place to add shared behaviour such as analytics or input routing later.
 */
UCLASS()
class GANTRYEXAMPLES_API UGTUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/* UUserWidget interface. */
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	/* UUserWidget interface. */

	/** Owning player controller, typed to the project class. Null in the widget designer. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|UI")
	AGTPlayerController* GetGTPlayerController() const;

	/** Owning HUD, typed to the project class. Null in the widget designer. */
	UFUNCTION(BlueprintPure, Category = "GantryExamples|UI")
	AGTHUD* GetGTHUD() const;
};
