#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "WarriorAbilitySystemComponent.generated.h"

struct FWarriorHeroAbilitySet;

UCLASS()
class WARRIOR_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    void OnAbilityInputPressed(const FGameplayTag& InTag);
    void OnAbilityInputReleased(const FGameplayTag& InTag);

    /**
     * Grant the specified abilities
     *
     * @param InAbilities the abilities to grant.
     * @param InApplyLevel the level at which to grant abilities.
     * @param OutGrantedAbilitySpecHandles the spec handles of the granted abilities.
     */
    UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta = (InApplyLevel = "1"))
    void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InAbilities,
                                  int32 InApplyLevel,
                                  TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

    /**
     * Remove abilities specified by the ability handles.
     *
     * @param InAbilitySpecHandles The AbilityHandles to clear.
     */
    UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
    void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) const TArray<FGameplayAbilitySpecHandle>& InAbilitySpecHandles);
};
