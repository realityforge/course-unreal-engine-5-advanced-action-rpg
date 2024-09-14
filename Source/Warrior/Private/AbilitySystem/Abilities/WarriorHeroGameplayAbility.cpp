#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Characters/HeroCharacter.h"
#include "Controllers/HeroPlayerController.h"
#include "WarriorGameplayTags.h"

AHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!HeroCharacterCache.IsValid() && IsValid(GetAvatarActorFromActorInfo()))
    {
        HeroCharacterCache = CastChecked<AHeroCharacter>(GetAvatarActorFromActorInfo());
    }
    return HeroCharacterCache.IsValid() ? HeroCharacterCache.Get() : nullptr;
}

AWarriorHeroPlayerController* UWarriorHeroGameplayAbility::GetWarriorHeroPlayerController()
{
    if (!WarriorHeroPlayerControllerCache.IsValid() && GetActorInfo().PlayerController.IsValid(false))
    {
        WarriorHeroPlayerControllerCache = CastChecked<AWarriorHeroPlayerController>(GetActorInfo().PlayerController);
    }
    return WarriorHeroPlayerControllerCache.IsValid() ? WarriorHeroPlayerControllerCache.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetCombatComponent();
}

FGameplayEffectSpecHandle
UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass,
                                                            const float InWeaponBaseDamage,
                                                            const FGameplayTag InCurrentAttackTypeTag,
                                                            const int32 InComboLevel) const
{
    check(InEffectClass);

    auto ContextHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    auto EffectSpecHandle = GetAbilitySystemComponentFromActorInfo_Checked()->MakeOutgoingSpec(InEffectClass,
                                                                                               GetAbilityLevel(),
                                                                                               ContextHandle);

    // Configure the SetByCaller modifiers
    {
        // Set the base damage
        EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
                                                       InWeaponBaseDamage);

        // Optionally set the combo level
        if (InCurrentAttackTypeTag.IsValid())
        {
            EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InComboLevel);
        }
    }

    return EffectSpecHandle;
}
