using UnrealBuildTool;

public class Warrior : ModuleRules
{
    public Warrior(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // clang-format off
        PublicDependencyModuleNames.AddRange(new []{
            "Aeon",
			"Core",
			"CoreUObject",
			"Engine",
			"EnhancedInput",
			"InputCore",
			"GameplayTags",
			"GameplayTasks",
            "GameplayAbilities"
        });
        // clang-format on

        PrivateDependencyModuleNames.AddRange(new string[0]);

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled
        // attribute set to true
    }
}