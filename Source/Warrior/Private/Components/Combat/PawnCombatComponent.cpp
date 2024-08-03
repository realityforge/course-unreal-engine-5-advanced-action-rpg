#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(const FGameplayTag InGameplayTag,
                                                 AWarriorWeaponBase* InWeapon,
                                                 const bool bInEquipWeapon)
{
    check(InWeapon);
    check(InGameplayTag.IsValid());
    checkf(!WeaponInventory.Contains(InGameplayTag),
           TEXT("A weapon named %s has already been registered under the tag named %s"),
           *InWeapon->GetName(),
           *InGameplayTag.ToString());
    WeaponInventory.Emplace(InGameplayTag, InWeapon);

    if (bInEquipWeapon)
    {
        EquippedWeaponTag = InGameplayTag;
    }

    Debug::Print(FString::Printf(TEXT("Weapon named %s has been registered using the tag %s"),
                                 *InWeapon->GetName(),
                                 *InGameplayTag.ToString()));
}

AWarriorWeaponBase* UPawnCombatComponent::GetWeaponInInventoryByTag(const FGameplayTag InGameplayTag) const
{
    return WeaponInventory.Contains(InGameplayTag) ? WeaponInventory.FindChecked(InGameplayTag) : nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetEquippedWeapon() const
{
    return EquippedWeaponTag.IsValid() ? GetWeaponInInventoryByTag(EquippedWeaponTag) : nullptr;
}
