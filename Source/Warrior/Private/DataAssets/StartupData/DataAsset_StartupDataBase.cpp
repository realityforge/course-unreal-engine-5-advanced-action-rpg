#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_StartupDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>> InGameplayAbilities,
                                                UWarriorAbilitySystemComponent* InWarriorAbilitySystemComponent,
                                                const int32 ApplyLevel)
{
    if (!InGameplayAbilities.IsEmpty())
    {
        for (const auto& Ability : InGameplayAbilities)
        {
            if (Ability)
            {
                FGameplayAbilitySpec AbilitySpec(Ability);
                AbilitySpec.SourceObject = InWarriorAbilitySystemComponent->GetAvatarActor();
                AbilitySpec.Level = ApplyLevel;

                InWarriorAbilitySystemComponent->GiveAbility(AbilitySpec);
            }
            else
            {
                // TODO: Log an error as StartUpData is very bad
            }
        }
    }
}

void UDataAsset_StartupDataBase::GiveToAbilitySystemComponent(
    UWarriorAbilitySystemComponent* InWarriorAbilitySystemComponent,
    int32 ApplyLevel)
{
    check(InWarriorAbilitySystemComponent);

    GrantAbilities(ActivateOnGivenAbilities, InWarriorAbilitySystemComponent, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InWarriorAbilitySystemComponent, ApplyLevel);
}
