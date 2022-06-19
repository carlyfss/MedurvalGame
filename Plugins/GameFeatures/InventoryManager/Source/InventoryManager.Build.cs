using UnrealBuildTool;

public class InventoryManager : ModuleRules
{
	public InventoryManager(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {  });

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"UMG", "Core", "CoreUObject", "Engine", "GameFeatures", "ModularGameplay", "EnhancedInput", "Medurval",
			"SlateCore", "CommonBase"
		});
	}
}