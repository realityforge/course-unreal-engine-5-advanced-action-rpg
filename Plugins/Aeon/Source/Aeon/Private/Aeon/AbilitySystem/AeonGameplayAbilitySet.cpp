#include "Aeon/AbilitySystem/AeonGameplayAbilitySet.h"
#include "Aeon/AbilitySystem/AeonGameplayAbility.h"

bool FAeonGameplayAbilitySet::IsValid() const
{
    return InputTag.IsValid() && Ability;
}
