#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroWeaponInInventoryByTag(FGameplayTag InGameplayTag) const
{
    return Cast<AWarriorHeroWeapon>(GetWeaponInInventoryByTag(InGameplayTag));
}
