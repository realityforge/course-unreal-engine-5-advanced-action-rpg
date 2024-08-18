#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}
