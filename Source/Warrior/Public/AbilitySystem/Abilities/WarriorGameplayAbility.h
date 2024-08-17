#pragma once

#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "CoreMinimal.h"
#include "WarriorGameplayAbility.generated.h"

class UWarriorAbilitySystemComponent;
class UPawnCombatComponent;

UCLASS(Abstract)
class WARRIOR_API UWarriorGameplayAbility : public UAeonGameplayAbility
{
    GENERATED_BODY()

protected:
    /** Return the CombatComponent from the associated Avatar Actor */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

    /** Return the WarriorAbilitySystemComponent from the associated Actor */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponentFromActorInfo() const;
};
