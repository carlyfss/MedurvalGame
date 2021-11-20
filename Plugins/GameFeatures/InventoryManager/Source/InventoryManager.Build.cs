// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class InventoryManager : ModuleRules
{
	public InventoryManager(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { });

		PrivateDependencyModuleNames.AddRange(new string[]
			{"UMG", "Core", "CoreUObject", "Engine", "GameFeatures", "ModularGameplay", "EnhancedInput", "Medurval"});
	}
}