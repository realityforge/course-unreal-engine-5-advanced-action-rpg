#pragma once

#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "CoreMinimal.h"
#include "WarriorEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AWarriorEnemyPlayerController;
class AEnemyCharacter;

UCLASS(Abstract)
class WARRIOR_API UWarriorEnemyGameplayAbility : public UWarriorGameplayAbility
{
    GENERATED_BODY()

    // Weak Object References will be reclaimed by Unreal when these objects are garbage collected

    TWeakObjectPtr<AEnemyCharacter> EnemyCharacterCache;

public:
    /** Return the physical representation of the owner, used for targeting and animation. This will often be null! */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    AEnemyCharacter* GetEnemyCharacterFromActorInfo();

    /** Return the CombatComponent from the associated Avatar Actor */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(UPARAM(DisplayName = "Effect Class",
                                                                meta = (AllowAbstract = "false"))
                                                             TSubclassOf<UGameplayEffect> InEffectClass,
                                                         UPARAM(ref, DisplayName = "Damage Scalable Float")
                                                             const FScalableFloat& InDamageScalableFloat);
};
