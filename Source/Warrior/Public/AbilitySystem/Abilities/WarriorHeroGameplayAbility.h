#pragma once

#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "CoreMinimal.h"
#include "WarriorHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AWarriorHeroPlayerController;
class AHeroCharacter;

UCLASS(Abstract)
class WARRIOR_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
    GENERATED_BODY()

    // Weak Object References will be reclaimed by Unreal when these objects are garbage collected

    TWeakObjectPtr<AHeroCharacter> HeroCharacterCache;
    TWeakObjectPtr<AWarriorHeroPlayerController> WarriorHeroPlayerControllerCache;

public:
    /** Return the physical representation of the owner, used for targeting and animation. This will often be null! */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    AHeroCharacter* GetHeroCharacterFromActorInfo();

    /** Return the PlayerController associated with the owning actor. This will often be null! */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    AWarriorHeroPlayerController* GetWarriorHeroPlayerController();

    /** Return the CombatComponent from the associated Avatar Actor */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
};
