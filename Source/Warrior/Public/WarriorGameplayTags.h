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
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_HeavyAttack_Axe)

    // --------------------------------------------------- //
    // Player Tags
    // --------------------------------------------------- //

    // Ability Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe)

    // Weapon Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

    // Event Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)

    // Status Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)

    // --------------------------------------------------- //
    // Enemy Tags
    // --------------------------------------------------- //

    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon)

    // --------------------------------------------------- //
    // Shared Tags (Used by both the Enemy and the Player)
    // --------------------------------------------------- //

    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)

} // namespace WarriorGameplayTags
