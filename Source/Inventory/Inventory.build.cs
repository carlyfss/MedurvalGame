using UnrealBuildTool;
 
public class Inventory : ModuleRules
{
	public Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 
		PublicIncludePaths.AddRange(new string[] {"Inventory/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Inventory/Private"});
		
		PublicDependencyModuleNames.AddRange(new string[] { 
			"CommonBase",
			"CommonUI",
			"EnhancedInput",
			"Medurval"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"UMG", 
			"Core", 
			"CoreUObject", 
			"Engine",
			"SlateCore"
		});
	}
}