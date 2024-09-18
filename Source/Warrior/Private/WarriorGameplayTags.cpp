#include "WarriorGameplayTags.h"

namespace WarriorGameplayTags
{
    // Input Tags
    UE_DEFINE_GAMEPLAY_TAG(Input_Native_Move, "Input.Native.Move")
    UE_DEFINE_GAMEPLAY_TAG(Input_Native_Look, "Input.Native.Look")

    UE_DEFINE_GAMEPLAY_TAG(Input_Ability_EquipAxe, "Input.Ability.EquipAxe")
    UE_DEFINE_GAMEPLAY_TAG(Input_Ability_UnequipAxe, "Input.Ability.UnequipAxe")

    UE_DEFINE_GAMEPLAY_TAG(Input_Ability_LightAttack_Axe, "Input.Ability.LightAttack.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Input_Ability_HeavyAttack_Axe, "Input.Ability.HeavyAttack.Axe")

    // --------------------------------------------------- //
    // Player Tags
    // --------------------------------------------------- //

    // Ability Tags
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe, "Player.Ability.Unequip.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause")

    // Weapon Tags
    UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe")

    // Event Tags
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Axe, "Player.Event.Unequip.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause")

    // Status Tags
    UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher")

    // Set By Caller Tags
    UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy")

    // --------------------------------------------------- //
    // Enemy Tags
    // --------------------------------------------------- //

    // Ability Tags
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged")

    UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")

    // --------------------------------------------------- //
    // Shared Tags (Used by both the Enemy and the Player)
    // --------------------------------------------------- //

    // Ability Tags
    UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")

    // Event Tags
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")

    // Set By Caller Tags
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage")

} // namespace WarriorGameplayTags
