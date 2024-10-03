#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Characters/EnemyCharacter.h"
#include "WarriorGameplayTags.h"

AEnemyCharacter* UWarriorEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!EnemyCharacterCache.IsValid() && IsValid(GetAvatarActorFromActorInfo()))
    {
        EnemyCharacterCache = CastChecked<AEnemyCharacter>(GetAvatarActorFromActorInfo());
    }
    return EnemyCharacterCache.IsValid() ? EnemyCharacterCache.Get() : nullptr;
}

UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetCombatComponent();
}

FGameplayEffectSpecHandle
// ReSharper disable once CppMemberFunctionMayBeConst
UWarriorEnemyGameplayAbility::MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass,
                                                         const FScalableFloat& InDamageScalableFloat)
{
    check(InEffectClass);

    const auto ASC = GetAbilitySystemComponentFromActorInfo_Checked();
    const int32 AbilityLevel = GetAbilityLevel();

    auto ContextHandle = ASC->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    auto EffectSpecHandle = ASC->MakeOutgoingSpec(InEffectClass, AbilityLevel, ContextHandle);
    // Configure the SetByCaller modifiers
    {
        // Set the base damage
        EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
                                                       InDamageScalableFloat.GetValueAtLevel(AbilityLevel));
    }

    return EffectSpecHandle;
}
