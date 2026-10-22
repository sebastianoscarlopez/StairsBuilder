using UnrealBuildTool;
using System.Collections.Generic;

public class StairsBuilderProjectEditorTarget : TargetRules
{
	public StairsBuilderProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange(new string[] { "StairsBuilderProject" });
	}
}
