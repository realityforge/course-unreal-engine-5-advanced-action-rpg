#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

// ReSharper disable once CppMemberFunctionMayBeStatic
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InGameplayAbilities,
                                                UWarriorAbilitySystemComponent* InAbilitySystemComponent,
                                                const int32 ApplyLevel)
{
    if (!InGameplayAbilities.IsEmpty())
    {
        for (const auto& Ability : InGameplayAbilities)
        {
            if (Ability)
            {
                FGameplayAbilitySpec AbilitySpec(Ability);
                AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
                AbilitySpec.Level = ApplyLevel;

                InAbilitySystemComponent->GiveAbility(AbilitySpec);
            }
            else
            {
                // TODO: Log an error as StartUpData is very bad
            }
        }
    }
}

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAbilitySystemComponent,
                                                              const int32 ApplyLevel)
{
    check(InAbilitySystemComponent);

    GrantAbilities(ActivateOnGivenAbilities, InAbilitySystemComponent, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InAbilitySystemComponent, ApplyLevel);
}
