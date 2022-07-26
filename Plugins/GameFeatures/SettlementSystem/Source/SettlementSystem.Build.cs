// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SettlementSystem : ModuleRules
{
	public SettlementSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { });

		PrivateIncludePaths.AddRange(new string[] { });

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine"
			});


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"CommonBase",
				"CommonUI",
				"UMG",
				"EnhancedInput",
				"GameplayTags",
				"Medurval"
			});
	}
}