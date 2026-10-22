using UnrealBuildTool;

public class StairsBuilderEditor : ModuleRules
{
	public StairsBuilderEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;

		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UnrealEd", "StairsBuilder" });
	}
}
