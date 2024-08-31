#pragma once

#include "Components/Combat/PawnCombatComponent.h"
#include "CoreMinimal.h"
#include "EnemyCombatComponent.generated.h"

class AWarriorHeroWeapon;

/**
 * Enemy specific combat component.
 */
UCLASS()
class WARRIOR_API UEnemyCombatComponent : public UPawnCombatComponent
{
    GENERATED_BODY()
};
