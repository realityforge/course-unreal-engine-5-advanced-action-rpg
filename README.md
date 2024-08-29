# Coursework for "Unreal Engine 5 C++: Advanced Action RPG"

This the project developed in the course [Unreal Engine 5 C++: Advanced Action RPG](https://www.udemy.com/course/unreal-engine-5-advanced-action-rpg/).

# Actions to Consider

* Convert `GA_Shared_SpawnWeapon` to C++ so that we can add better validation rules (ala `meta=(RuleRangerRequired="true")`)
* Add RuleRanger rule to ensure `GA_Shared_SpawnWeapon` has data-only blueprints as subclasses? 

* Convert SendGameplayEventToOwner to C++
  - Ensure bShouldFireInEditor is False
  - Specify a "Known" color?
  - Add (`meta=(RuleRangerRequired="true")`) to Tag
  - Restrict Tag to Player.Event subtags?

* Merge GA_Hero_HeavyAttack_Base and GA_Hero_LightAttack_Base or at least merge commonality. Consider making into C++ or otherwise force all subclasses to be Data-only?

* Document how to give player equipment at start
* Document how equipment when equipped will give the player an ability
* Document how to give player an input action
