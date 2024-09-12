#include "Components/Combat/PawnCombatComponent.h"
#include "Aeon/Logging.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(const FGameplayTag InGameplayTag,
                                                 AWarriorWeaponBase* InWeapon,
                                                 const bool bInEquipWeapon)
{
    check(InWeapon);
    check(InGameplayTag.IsValid());
    checkf(!WeaponInventory.Contains(InGameplayTag),
           TEXT("A weapon named %s has already been registered under the "
                "tag named %s when attempting to register %s"),
           *WeaponInventory.FindChecked(InGameplayTag)->GetName(),
           *InGameplayTag.ToString(),
           *InWeapon->GetName());
    AEON_INFO_LOG(TEXT("Registering weapon named %s under tag %s for actor %s"),
                  *InWeapon->GetName(),
                  *InGameplayTag.ToString(),
                  *GetOwner()->GetName());
    WeaponInventory.Emplace(InGameplayTag, InWeapon);

    if (bInEquipWeapon)
    {
        EquippedWeaponTag = InGameplayTag;
    }
}

AWarriorWeaponBase* UPawnCombatComponent::GetWeaponInInventoryByTag(const FGameplayTag InGameplayTag) const
{
    return WeaponInventory.Contains(InGameplayTag) ? WeaponInventory.FindChecked(InGameplayTag) : nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetEquippedWeapon() const
{
    return EquippedWeaponTag.IsValid() ? GetWeaponInInventoryByTag(EquippedWeaponTag) : nullptr;
}

void UPawnCombatComponent::ToggleWeaponCollision(const bool bShouldEnable,
                                                 const EToggleDamageType ToggleDamageType) const
{
    if (EToggleDamageType::CurrentEquippedWeapon == ToggleDamageType)
    {
        // ReSharper disable once CppTooWideScopeInitStatement
        const auto Weapon = GetEquippedWeapon();
        if (ensureAlwaysMsgf(Weapon,
                             TEXT("UPawnCombatComponent::ToggleWeaponCollision "
                                  "invoked when no weapon equipped")))
        {
            if (bShouldEnable)
            {
                Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            }
            else
            {
                Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            }
        }
    }
    else
    {
        ensureAlwaysMsgf(false,
                         TEXT("UPawnCombatComponent::ToggleWeaponCollision invoked "
                              "with unknown ToggleDamageType %d"),
                         ToggleDamageType);
    }
}
