// Copyright Private Asylum LLC, 2026, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GantryExamplesServerTarget : TargetRules
{
	public GantryExamplesServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;

		GantryExamplesTarget.ApplySharedGantryExamplesTargetSettings(this);

		ExtraModuleNames.Add("GantryExamples");
	}
}
