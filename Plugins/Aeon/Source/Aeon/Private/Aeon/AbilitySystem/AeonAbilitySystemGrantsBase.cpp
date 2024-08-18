#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/Logging.h"

// ReSharper disable once CppMemberFunctionMayBeStatic
void UAeonAbilitySystemGrantsBase::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities,
                                                  UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                  const int32 ApplyLevel)
{
    if (!InGameplayAbilities.IsEmpty())
    {
        for (int32 i = 0; i < InGameplayAbilities.Num(); i++)
        {
            if (const auto& Ability = InGameplayAbilities[i])
            {
                FGameplayAbilitySpec AbilitySpec(Ability, ApplyLevel);
                AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();

                InAbilitySystemComponent->GiveAbility(AbilitySpec);
            }
            else
            {
                AEON_WARNING_ALOG("UAeonAbilitySystemGrantsBase::GrantAbilities: "
                                  "Invalid Ability specified at index %d of "
                                  "StartUpAbilitySets can not be granted. IN asset %s",
                                  i,
                                  *GetName());
            }
        }
    }
}

void UAeonAbilitySystemGrantsBase::GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                                const int32 ApplyLevel)
{
    check(InAbilitySystemComponent);

    GrantAbilities(ActivateOnGivenAbilities, InAbilitySystemComponent, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InAbilitySystemComponent, ApplyLevel);
}
