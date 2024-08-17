using UnrealBuildTool;

public class Aeon : ModuleRules
{
    public Aeon(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] {});
        PrivateIncludePaths.AddRange(new string[] {});
        PublicDependencyModuleNames.AddRange(new[] {
            "Core",
        });
        PrivateDependencyModuleNames.AddRange(new[] {
            "CoreUObject",
            "Engine",
        });
        DynamicallyLoadedModuleNames.AddRange(new string[] {});
    }
}
