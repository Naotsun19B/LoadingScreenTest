// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class CustomLoadingScreen : ModuleRules
	{
		public CustomLoadingScreen(ReadOnlyTargetRules Target)
            : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PrivateIncludePaths.Add("CustomLoadingScreen/Private");

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"MoviePlayer",
					"Slate",
					"SlateCore",
					"InputCore",
					"Engine"
				});
		}
	}
}
