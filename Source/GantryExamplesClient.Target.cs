// Copyright Private Asylum LLC, 2026, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GantryExamplesClientTarget : TargetRules
{
	public GantryExamplesClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;

		GantryExamplesTarget.ApplySharedGantryExamplesTargetSettings(this);

		ExtraModuleNames.Add("GantryExamples");
	}
}
