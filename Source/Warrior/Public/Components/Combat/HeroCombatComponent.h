#pragma once

#include "Components/Combat/PawnCombatComponent.h"
#include "CoreMinimal.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;
/**
 * Hero (a.k.a. Player) specific combat component.
 */
UCLASS()
class WARRIOR_API UHeroCombatComponent : public UPawnCombatComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    AWarriorHeroWeapon* GetHeroWeaponInInventoryByTag(FGameplayTag InGameplayTag) const;
};
