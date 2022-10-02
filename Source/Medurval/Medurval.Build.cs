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
			"Core",
			"CoreUObject",
			"Engine",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"InputCore",
			"UMG",
			"Slate",
			"SlateCore",
			"MoviePlayer"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameFeatures",
			"CommonUI",
			"ModularGameplay",
			"EnhancedInput",
			"MDLoadingScreen"
		});
	}
}