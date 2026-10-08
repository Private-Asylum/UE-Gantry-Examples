// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

/**
 * Slate style set for the project's editor UI.
 *
 * Deliberately holds no image brushes yet: every icon below borrows from FAppStyle, so the module
 * has no asset dependencies and cannot fail to load on a fresh clone. To add project artwork, drop
 * SVGs under Content/Editor/Slate and register them in Create() with IMAGE_BRUSH_SVG.
 */
class FGTEditorStyle
{
public:

	/** Creates and registers the style set. Safe to call once, from module startup. */
	static void Initialize();

	/** Unregisters and destroys the style set. */
	static void Shutdown();

	/** Re-reads textures after a hot reload of the style. */
	static void ReloadTextures();

	/** The registered style set. Only valid between Initialize and Shutdown. */
	static const ISlateStyle& Get();

	/** Name the style set is registered under. */
	static FName GetStyleSetName();

private:

	/** Builds the style set. */
	static TSharedRef<class FSlateStyleSet> Create();

	/** The one instance, owned by this class. */
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
