#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorHeroWeapon.generated.h"

UCLASS()
class WARRIOR_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
    GENERATED_BODY()

    // The currently assigned ability handles.
    // We cache them so that we can clear the abilities later.
    TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;

public:
    /** Data specific to the type of weapon. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
    FWarriorHeroWeaponData HeroWeaponData;

    /**
     * Assign the AbilitySpecHandles to the weapon.
     * This is called when the weapon is equipped. We want to retain the handles so that we can clear the abilities when
     * the weapon is un-equipped.
     *
     * @param InAbilityHandles The Handles to Assign
     */
    UFUNCTION(BlueprintCallable)
    void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InAbilityHandles);

    /**
     * Return the currently assigned ability spec handles.
     * This will be empty if the weapon grants no abilities or is not equipped.
     *
     * @return the currently assigned ability spec handles.
     */
    UFUNCTION(BlueprintPure)
    TArray<FGameplayAbilitySpecHandle> GetGrantedAbilityHandles() const;
};
