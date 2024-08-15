#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Aeon/Logging.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InTag)
{
    if (ensure(InTag.IsValid()))
    {
        bool bActivationOccurred = false;
        for (const auto AbilitySpec : GetActivatableAbilities())
        {
            if (AbilitySpec.DynamicAbilityTags.HasTagExact(InTag))
            {
                TryActivateAbility(AbilitySpec.Handle);
                bActivationOccurred = true;
            }
        }
        if (!bActivationOccurred)
        {

            AEON_WARNING_ALOG("UWarriorAbilitySystemComponent::OnAbilityInputPressed: "
                              "Unable to activate any ability with tag %s",
                              *InTag.ToString());
        }
    }
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InTag) {}
