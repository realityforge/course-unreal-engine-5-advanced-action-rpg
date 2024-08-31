#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "Characters/EnemyCharacter.h"

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
