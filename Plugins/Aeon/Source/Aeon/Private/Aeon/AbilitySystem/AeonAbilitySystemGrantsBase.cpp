#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/Logging.h"

void UAeonAbilitySystemGrantsBase::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities,
                                                  UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                  const int32 ApplyLevel) const
{
    int32 AbilityIndex = 0;
    for (const auto& AbilityClass : InGameplayAbilities)
    {
        if (AbilityClass)
        {
            FGameplayAbilitySpec AbilitySpec(AbilityClass, ApplyLevel);
            AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();

            InAbilitySystemComponent->GiveAbility(AbilitySpec);
        }
        else
        {
            AEON_WARNING_ALOG("UAeonAbilitySystemGrantsBase::GrantAbilities: "
                              "Invalid Ability specified at index %d of "
                              "AbilitySets can not be granted. In asset %s",
                              AbilityIndex,
                              *GetName());
        }
        AbilityIndex++;
    }
}

void UAeonAbilitySystemGrantsBase::GrantEffects(const TArray<TSubclassOf<UGameplayEffect>>& InGameplayEffects,
                                                UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                const int32 ApplyLevel) const
{
    int32 EffectIndex = 0;
    for (const auto& EffectClass : InGameplayEffects)
    {
        if (EffectClass)
        {
            const auto EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
            const auto EffectContext = InAbilitySystemComponent->MakeEffectContext();
            InAbilitySystemComponent->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, EffectContext);
        }
        else
        {
            AEON_WARNING_ALOG("UAeonAbilitySystemGrantsBase::GrantEffects: "
                              "Invalid Effect specified at index %d of "
                              "GameplayEffects can not be granted. In asset %s",
                              EffectIndex,
                              *GetName());
        }
        EffectIndex++;
    }
}

void UAeonAbilitySystemGrantsBase::GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                                const int32 ApplyLevel)
{
    check(InAbilitySystemComponent);

    GrantAbilities(ActivateOnGivenAbilities, InAbilitySystemComponent, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InAbilitySystemComponent, ApplyLevel);
    GrantEffects(GameplayEffects, InAbilitySystemComponent, ApplyLevel);
}
