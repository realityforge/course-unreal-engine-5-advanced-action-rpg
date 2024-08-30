#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"

void UAeonGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);
    if (EAeonAbilityActivationPolicy::OnGiven == AbilityActivationPolicy)
    {
        if (ActorInfo && !Spec.IsActive())
        {
            ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
        }
    }
}

void UAeonGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      const bool bReplicateEndAbility,
                                      const bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // If an activation policy is OnGiven then we remove it after the ability completes
    if (EAeonAbilityActivationPolicy::OnGiven == AbilityActivationPolicy)
    {
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}

UAeonAbilitySystemComponent* UAeonGameplayAbility::GetAeonAbilitySystemComponentFromActorInfo() const
{
    return CastChecked<UAeonAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}
