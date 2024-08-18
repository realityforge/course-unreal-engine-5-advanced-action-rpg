#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"

// ReSharper disable once CppMemberFunctionMayBeStatic
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InGameplayAbilities,
                                                UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                const int32 ApplyLevel)
{
    if (!InGameplayAbilities.IsEmpty())
    {
        for (const auto& Ability : InGameplayAbilities)
        {
            if (Ability)
            {
                FGameplayAbilitySpec AbilitySpec(Ability, ApplyLevel);
                AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();

                InAbilitySystemComponent->GiveAbility(AbilitySpec);
            }
            else
            {
                // TODO: Log an error as StartUpData is very bad
            }
        }
    }
}

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                              const int32 ApplyLevel)
{
    check(InAbilitySystemComponent);

    GrantAbilities(ActivateOnGivenAbilities, InAbilitySystemComponent, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InAbilitySystemComponent, ApplyLevel);
}
