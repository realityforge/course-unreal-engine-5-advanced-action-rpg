#pragma once

#include "AbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonAttributeSet.h"
#include "WarriorAttributeSet.generated.h"

class IPawnUIInterface;
/**
 * Attributes used within Warrior game.
 */
UCLASS()
class WARRIOR_API UWarriorAttributeSet : public UAeonAttributeSet
{
    GENERATED_BODY()

    // Cache the PawnUIInterface associated with attributes
    // so we don't have to keep unnecessarily casting
    TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;

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

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
