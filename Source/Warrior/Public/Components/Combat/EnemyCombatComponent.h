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

protected:
#pragma region UPawnCombatComponent Interface
    virtual void OnHitTargetActor(AActor* HitActor) override;
#pragma endregion
};
