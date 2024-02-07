// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GAUIDialog : ModuleRules
{
	public GAUIDialog(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                ModuleDirectory,
                ModuleDirectory + "/GAUIDialog",
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine",

                "Slate", "SlateCore", "UMG", "CommonUI", 

                "GUIExt",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "DeveloperSettings",

                "InputCore", "EnhancedInput", "CommonInput", 
            }
        );
    }
}
