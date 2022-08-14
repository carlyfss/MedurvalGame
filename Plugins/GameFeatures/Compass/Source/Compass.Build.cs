// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Compass : ModuleRules
{
	public Compass(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {});
		
		PrivateIncludePaths.AddRange(new string[] {});
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CommonBase"
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"UMG"
			});
	}
}
