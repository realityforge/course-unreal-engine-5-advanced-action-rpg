#pragma once

#include "AbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonAttributeSet.h"
#include "WarriorAttributeSet.generated.h"

/**
 * Attributes used within Warrior game.
 */
UCLASS()
class WARRIOR_API UWarriorAttributeSet : public UAeonAttributeSet
{
    GENERATED_BODY()

public:
    /** The current health of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData CurrentHealth;

    /** The maximum health of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData MaxHealth;

    /** The current rage of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Rage")
    FGameplayAttributeData CurrentRage;

    /** The maximum rage of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Rage")
    FGameplayAttributeData MaxRage;

    // Public temporarily to capture in UGEExecCalc_DamageTaken

    /** The attack power of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData AttackPower;

    /** The defense power of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData DefensePower;

    /** The damage taken by the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData DamageTaken;

    UWarriorAttributeSet();

    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentRage)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxRage)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackPower)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefensePower)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DamageTaken)
};
