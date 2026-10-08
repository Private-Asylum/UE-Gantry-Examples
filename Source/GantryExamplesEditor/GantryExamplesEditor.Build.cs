// Copyright Private Asylum LLC, 2026, All Rights Reserved.

using UnrealBuildTool;

public class GantryExamplesEditor : ModuleRules
{
	public GantryExamplesEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"GantryExamples"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"InputCore",
			"Slate",
			"SlateCore",
			"ToolMenus",
			"UnrealEd",
			"EditorFramework",
			"EditorSubsystem",
			"DeveloperSettings",
			"GameplayTags",
			"Projects",
			"DataValidation",
			"AssetRegistry",
			"Settings",
			"GantryCore",
			"GantryCoreEditor",
			"GantryGauge",
			"GantryGaugeEditor",
			"GantryExperience"
		});
	}
}
