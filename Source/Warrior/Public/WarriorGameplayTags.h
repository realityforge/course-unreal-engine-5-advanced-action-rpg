#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
    // --------------------------------------------------- //
    // Input Tags
    // --------------------------------------------------- //

    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Move)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Look)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_EquipAxe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_UnequipAxe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_LightAttack_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Ability_HeavyAttack_Axe)

    // --------------------------------------------------- //
    // GameplayCue Tags
    // --------------------------------------------------- //

    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Sounds_MeleeHit_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Sounds_Death_Guardian)

    // --------------------------------------------------- //
    // Player Tags
    // --------------------------------------------------- //

    // Ability Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause)

    // Weapon Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

    // Event Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause)

    // Status Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)

    // SetByCaller Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy)

    // --------------------------------------------------- //
    // Enemy Tags
    // --------------------------------------------------- //

    // Ability Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged)

    // Weapon Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon)

    // Status Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing)

    // --------------------------------------------------- //
    // Shared Tags (Used by both the Enemy and the Player)
    // --------------------------------------------------- //

    // Ability Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death)

    // Event Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact)

    // SetByCaller Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage)

    // Status Tags
    WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead)
} // namespace WarriorGameplayTags
