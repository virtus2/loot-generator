// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LootGen : ModuleRules
{
	public LootGen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
