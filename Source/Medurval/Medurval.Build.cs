// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

// ReSharper disable once InconsistentNaming
public class Medurval : ModuleRules
{
	public Medurval(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities", "GameplayTags", "GameplayTasks", "Core", "CoreUObject", "Engine", "InputCore",
			"GameFeatures", "ModularGameplay", "EnhancedInput", "CommonUI"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UMG", "CommonBase", "CommonUI"
		});
	}
}