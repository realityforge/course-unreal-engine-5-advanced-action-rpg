#include "Items/Weapons/WarriorHeroWeapon.h"

void AWarriorHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InAbilityHandles)
{
    GrantedAbilityHandles = InAbilityHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarriorHeroWeapon::GetGrantedAbilityHandles() const
{
    return GrantedAbilityHandles;
}
