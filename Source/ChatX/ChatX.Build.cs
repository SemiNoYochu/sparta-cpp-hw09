// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ChatX : ModuleRules
{
	public ChatX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
			{
				// Inintaial Dependency
				"Core", "CoreUObject", "Engine", "InputCore",
				
				// UI
				"UMG", "Slate", "SlateCore",
			});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] { "ChatX" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
