#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
    // Input Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Move)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Look)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_EquipAxe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_UnequipAxe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_LightAttack_Axe)

    // Player Tags

    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)

    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

    // Event Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)

} // namespace WarriorGameplayTags
