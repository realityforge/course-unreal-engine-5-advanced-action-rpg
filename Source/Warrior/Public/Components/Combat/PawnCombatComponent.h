#pragma once

#include "Components/PawnExtensionComponentBase.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AWarriorWeaponBase;
/**
 * Abstract component with combat related functionality that is shared between the Hero/Enemy classes.
 */
UCLASS(Abstract)
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
    GENERATED_BODY()

    /** The current weapons carried by actor. */
    TMap<FGameplayTag, AWarriorWeaponBase*> WeaponInventory;

    /** The tag identifying the currently equipped weapon. */
    UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat", meta = (AllowPrivateAccess = "true"))
    FGameplayTag EquippedWeaponTag{ FGameplayTag::EmptyTag };

public:
    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    void RegisterSpawnedWeapon(FGameplayTag InGameplayTag, AWarriorWeaponBase* InWeapon, bool bInEquipWeapon = false);

    /** Return the weapon in inventory that is identified by the specified tag. */
    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    AWarriorWeaponBase* GetWeaponInInventoryByTag(FGameplayTag InGameplayTag) const;

    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    AWarriorWeaponBase* GetEquippedWeapon() const;
};
