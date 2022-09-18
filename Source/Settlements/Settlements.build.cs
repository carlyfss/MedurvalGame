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
				"CommonUI",
				"Inventory",
				"Medurval",
				"EnhancedInput"
			});


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"UMG",
				"GameplayTags"
			});
	}
}