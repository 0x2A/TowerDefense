// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class StrategyGameLoadingScreen : ModuleRules
{
    public StrategyGameLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateIncludePaths.Add("../../StrategyGame/Source/StrategyGameLoadingScreen/Private");

        PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine"
			}
		);

        PrivateDependencyModuleNames.AddRange(
			new string[] {
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
}
