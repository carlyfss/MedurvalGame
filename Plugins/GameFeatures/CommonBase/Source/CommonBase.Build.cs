// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CommonBase : ModuleRules
{
	public CommonBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { });

		PrivateIncludePaths.AddRange(new string[] { });


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "Engine", "EnhancedInput",
				// ... add other public dependencies that you statically link with here ...
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG"
				// ... add private dependencies that you statically link with here ...	
			}
		);
	}
}