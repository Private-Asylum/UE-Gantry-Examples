// Copyright Private Asylum LLC, 2026, All Rights Reserved.

using UnrealBuildTool;

public class GantryExamples : ModuleRules
{
	public GantryExamples(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Make the module root an include root so headers are addressed by their category path,
		// e.g. #include "World/GameMode/GTGameMode.h".
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayTags",
			"DeveloperSettings",
			"AIModule",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"ApplicationCore",
			"Projects",
			"RenderCore"
		});

		// The Gantry plugin is where the real systems live; this project is its proving ground.
		// Public because GTAssetManager.h derives from a Gantry class in its own public header.
		PublicDependencyModuleNames.AddRange(new string[] { "GantryCore", "GantryGauge", "GantryExperience" });
		PrivateDependencyModuleNames.Add("GantryGaugeUI");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
