#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WarriorStructTypes.generated.h"

class UWarriorHeroLinkedAnimLayer;
class UWarriorGameplayAbility;

/**
 * Definition of an ability that can be granted to a Hero.
 */
USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
    GENERATED_BODY()

    /** Tag to identify the Ability. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag Tag;

    /** The Ability. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UWarriorGameplayAbility> Ability;

    bool IsValid() const;
};

/**
 * Data describing a type of weapon.
 */
USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
    GENERATED_BODY()

    /** The AnimLayer that we need to link when this weapon is equipped. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayer;
};
