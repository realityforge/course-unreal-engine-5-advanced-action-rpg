#pragma once

#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "CoreMinimal.h"
#include "WarriorGameplayAbility.generated.h"

class UAeonAbilitySystemComponent;
class UPawnCombatComponent;

UCLASS(Abstract)
class WARRIOR_API UWarriorGameplayAbility : public UAeonGameplayAbility
{
    GENERATED_BODY()

protected:
    /** Return the CombatComponent from the associated Avatar Actor */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
};
