// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

/**
 * Natively declared gameplay tags.
 *
 * Declaring tags in C++ rather than only in the tag table means the compiler catches typos and
 * a rename is a rename, not a silent runtime mismatch. Add the matching entry to
 * Config/DefaultGameplayTags.ini only when designers need to author it.
 */
namespace GTGameplayTags
{
	/* Input. Bound by UGTInputConfig to Enhanced Input actions. */
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Look);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Jump);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Crouch);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Sprint);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Interact);

	/* Player state. Broad states a controller or pawn can be in. */
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Alive);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dead);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Spectating);

	/* UI. Identifies HUD layers so widgets can be pushed and popped by tag. */
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Game);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Menu);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Debug);
	
	/* Tag boilerplate for demonstrating Experiences. */
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Experience_Base);
	GANTRYEXAMPLES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Experience_Sandbox);
}
