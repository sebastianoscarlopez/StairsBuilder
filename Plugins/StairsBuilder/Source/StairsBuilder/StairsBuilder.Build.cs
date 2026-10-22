using UnrealBuildTool;

public class StairsBuilder : ModuleRules
{
	public StairsBuilder(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine" });
		PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject" });
	}
}
