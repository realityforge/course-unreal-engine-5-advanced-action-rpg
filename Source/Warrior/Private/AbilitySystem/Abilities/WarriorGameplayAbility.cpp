#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

FActiveGameplayEffectHandle
UWarriorGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
                                                          const FGameplayEffectSpecHandle& InSpecHandle,
                                                          EWarriorSuccessType& OutSuccessType)
{
    const auto Handle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
    OutSuccessType = Handle.WasSuccessfullyApplied() ? EWarriorSuccessType::Successful : EWarriorSuccessType::Failed;
    return Handle;
}

FActiveGameplayEffectHandle
UWarriorGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
                                                             const FGameplayEffectSpecHandle& InSpecHandle) const
{
    checkf(InSpecHandle.IsValid(),
           TEXT("Attempted to apply EffectSpecHandle to target %s but the SpecHandle is invalid"),
           *TargetActor->GetActorNameOrLabel());
    const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
    checkf(TargetASC,
           TEXT("Attempted to apply EffectSpecHandle to target %s that has no associated AbilitySystemComponent"),
           *TargetActor->GetActorNameOrLabel());

    const auto ASC = GetAbilitySystemComponentFromActorInfo_Checked();
    return ASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}
