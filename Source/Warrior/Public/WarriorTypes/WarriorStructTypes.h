#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "WarriorStructTypes.generated.h"

struct FAeonGameplayAbilitySet;
class UInputMappingContext;
class UWarriorHeroLinkedAnimLayer;
class UWarriorGameplayAbility;

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
    TArray<FAeonGameplayAbilitySet> DefaultWeaponAbilities;

    /** The Base Damage of the Weapon. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FScalableFloat WeaponBaseDamage;

    /** The Icon representing the Weapon that can be placed on the HUD. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};
