#include "Components/Combat/PawnCombatComponent.h"
#include "Aeon/Logging.h"
#include "Items/Weapons/WarriorWeaponBase.h"

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

    AEON_SHOW_INFO_MESSAGE(TEXT("Weapon named %s has been registered using the tag %s Equip?=%s"),
                           *InWeapon->GetName(),
                           *InGameplayTag.ToString(),
                           bInEquipWeapon ? TEXT("True") : TEXT("False"));
}

AWarriorWeaponBase* UPawnCombatComponent::GetWeaponInInventoryByTag(const FGameplayTag InGameplayTag) const
{
    return WeaponInventory.Contains(InGameplayTag) ? WeaponInventory.FindChecked(InGameplayTag) : nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetEquippedWeapon() const
{
    return EquippedWeaponTag.IsValid() ? GetWeaponInInventoryByTag(EquippedWeaponTag) : nullptr;
}
