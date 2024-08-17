#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WarriorStructTypes.generated.h"

class UInputMappingContext;
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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input"))
    FGameplayTag InputTag;

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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowAbstract = "false"))
    TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayer;

    /** The InputMappingContext that is added to the owner when the weapon is equipped. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputMappingContext> InputMappingContext;

    /** The Abilities that are granted to the owner when the weapon is equipped */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities;
};
