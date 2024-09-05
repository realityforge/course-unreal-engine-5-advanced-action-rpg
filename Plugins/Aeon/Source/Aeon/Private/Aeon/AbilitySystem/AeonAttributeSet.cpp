#include "Aeon/AbilitySystem/AeonAttributeSet.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"

UAeonAbilitySystemComponent* UAeonAttributeSet::GetAeonAbilitySystemComponent() const
{
    return CastChecked<UAeonAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
