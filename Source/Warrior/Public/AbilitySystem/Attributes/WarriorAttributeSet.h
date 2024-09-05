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

    /** The current health of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData CurrentHealth;

    /** The maximum health of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData MaxHealth;

    /** The current rage of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Rage", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData CurrentRage;

    /** The maximum rage of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Rage", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData MaxRage;

    /** The attack power of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData AttackPower;

    /** The defense power of the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData DefensePower;

    /** The damage taken by the character. */
    UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData DamageTaken;

public:
    UWarriorAttributeSet();

    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentRage)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxRage)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackPower)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefensePower)
    ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DamageTaken)
};
