// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Andromeda : ModuleRules
{
	public Andromeda(ReadOnlyTargetRules Target) : base(Target)
	{
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(new string[] { "SkeletalMerging" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Niagara" });
	}
}
