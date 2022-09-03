using UnrealBuildTool;
 
public class Settlements : ModuleRules
{
	public Settlements(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {"Settlements/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Settlements/Private"});
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"CommonBase",
				"CommonUI",
				"Medurval",
				"Inventory"
			});


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"UMG",
				"EnhancedInput",
				"GameplayTags"
			});
	}
}