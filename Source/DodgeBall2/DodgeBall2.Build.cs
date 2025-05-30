// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DodgeBall2 : ModuleRules
{
	public DodgeBall2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });
	}
}
