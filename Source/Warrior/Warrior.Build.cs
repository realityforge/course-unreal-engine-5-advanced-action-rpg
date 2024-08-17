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
    }
}