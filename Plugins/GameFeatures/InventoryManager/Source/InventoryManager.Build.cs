using UnrealBuildTool;

public class InventoryManager : ModuleRules
{
	public InventoryManager(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"CommonBase",
			"EnhancedInput", 
			"Medurval"  
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"UMG", 
			"Core", 
			"CoreUObject", 
			"Engine",
			"SlateCore", 
			
		});
	}
}