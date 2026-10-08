// Copyright Private Asylum LLC, 2026, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GantryExamplesEditorTarget : TargetRules
{
	public GantryExamplesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		GantryExamplesTarget.ApplySharedGantryExamplesTargetSettings(this);

		ExtraModuleNames.AddRange(new string[] { "GantryExamples", "GantryExamplesEditor" });
	}
}
