#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{
    return CastChecked<UWarriorAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}
