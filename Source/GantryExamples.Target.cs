// Copyright Private Asylum LLC, 2026, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using Microsoft.Extensions.Logging;

public class GantryExamplesTarget : TargetRules
{
	public GantryExamplesTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ApplySharedGantryExamplesTargetSettings(this);

		ExtraModuleNames.Add("GantryExamples");
	}

	/**
	 * Settings shared by every GantryExamples target.
	 *
	 * Keeping these in one place means the Game, Client, Server and Editor targets can never
	 * drift apart on build settings, which is the usual source of "works in editor, breaks in
	 * a cooked build" surprises.
	 */
	internal static void ApplySharedGantryExamplesTargetSettings(TargetRules Target)
	{
		ILogger Logger = Target.Logger;

		Target.DefaultBuildSettings = BuildSettingsVersion.Latest;
		Target.IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		bool bIsTest = Target.Configuration == UnrealTargetConfiguration.Test;
		bool bIsShipping = Target.Configuration == UnrealTargetConfiguration.Shipping;
		bool bIsDedicatedServer = Target.Type == TargetType.Server;

		if (Target.BuildEnvironment == TargetBuildEnvironment.Unique)
		{
			Logger.LogInformation("GantryExamples: applying Unique build environment settings.");

			// Shadowed variables are almost always a bug waiting to happen. Treat them as one.
			Target.CppCompileWarningSettings.ShadowVariableWarningLevel = WarningLevel.Error;

			// Keep logging available in Shipping so field builds remain diagnosable.
			Target.bUseLoggingInShipping = true;

			if (bIsShipping && !bIsDedicatedServer)
			{
				Target.bDisableUnverifiedCertificates = true;
			}

			if (bIsShipping || bIsTest)
			{
				// Don't read generated / non-UFS ini files out of a cooked build.
				Target.bAllowGeneratedIniWhenCooked = false;
				Target.bAllowNonUFSIniWhenCooked = false;
			}

			if (Target.Type != TargetType.Editor)
			{
				// The path tracer is a beauty-shot tool only, and OpenImageDenoise is a very large DLL.
				Target.DisablePlugins = new List<string>(new string[] { "OpenImageDenoise" });
			}
		}
	}
}
