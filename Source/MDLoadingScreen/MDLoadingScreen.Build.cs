// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class MDLoadingScreen : ModuleRules
{
	public MDLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "Public/MDLoadingScreen.h";

		PCHUsage = PCHUsageMode.UseSharedPCHs;

		PublicIncludePaths.Add("MDLoadingScreen/Public");
		PrivateIncludePaths.Add("MDLoadingScreen/Private");

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}