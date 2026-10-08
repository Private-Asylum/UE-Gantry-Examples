// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Core/Tags/GTGameplayTags.h"

namespace GTGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Move, "Input.Move", "Two axis movement input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Look, "Input.Look", "Two axis look input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Jump, "Input.Jump", "Jump input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Crouch, "Input.Crouch", "Crouch toggle or hold input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Sprint, "Input.Sprint", "Sprint toggle or hold input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Interact, "Input.Interact", "Interact with the focused actor.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Alive, "State.Alive", "Pawn is alive and controllable.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Dead, "State.Dead", "Pawn is dead and awaiting respawn.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Spectating, "State.Spectating", "Player is spectating rather than playing.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Game, "UI.Layer.Game", "Always-on gameplay HUD layer.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Menu, "UI.Layer.Menu", "Full screen menu layer.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Modal, "UI.Layer.Modal", "Blocking modal dialog layer.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_Layer_Debug, "UI.Layer.Debug", "Developer overlay layer.");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Experience_Base, "GT.Experience.Base", "Base experience tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Experience_Sandbox, "GT.Experience.Sandbox", "Sandbox experience tag.");
}
