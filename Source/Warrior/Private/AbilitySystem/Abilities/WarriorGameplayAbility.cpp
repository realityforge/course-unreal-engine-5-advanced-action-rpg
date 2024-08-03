#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);
    if (EWarriorAbilityActivationPolicy::OnGiven == AbilityActivationPolicy)
    {
        if (ActorInfo && !Spec.IsActive())
        {
            ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
        }
    }
}

void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const bool bReplicateEndAbility,
                                         const bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // If an activation policy is OnGiven then we remove it after the ability completes
    if (EWarriorAbilityActivationPolicy::OnGiven == AbilityActivationPolicy)
    {
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}
