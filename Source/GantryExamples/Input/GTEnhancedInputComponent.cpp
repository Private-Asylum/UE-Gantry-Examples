// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Input/GTEnhancedInputComponent.h"

void UGTEnhancedInputComponent::RemoveAllBindings()
{
	// Called when a pawn is unpossessed so stale handlers do not fire against a dead object.
	ClearActionEventBindings();
	ClearActionValueBindings();
	ClearDebugKeyBindings();
}
