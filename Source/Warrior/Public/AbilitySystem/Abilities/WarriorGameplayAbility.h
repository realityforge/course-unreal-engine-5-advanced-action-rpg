#pragma once

#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "CoreMinimal.h"
#include "WarriorTypes/WarriorEnumTypes.h"
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

    // TODO: Migrate to Aeon?
    /** Apply the EffectSpecHandle to the specified Target */
    UFUNCTION(BlueprintCallable,
              DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor",
              Category = "Warrior|Ability",
              meta = (ExpandEnumAsExecs = "OutSuccessType"))
    FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
                                                                 const FGameplayEffectSpecHandle& InSpecHandle,
                                                                 EWarriorSuccessType& OutSuccessType);

    // TODO: Migrate to Aeon?
    FActiveGameplayEffectHandle
    NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle) const;
};
