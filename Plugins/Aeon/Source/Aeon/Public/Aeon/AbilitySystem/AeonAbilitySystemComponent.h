#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AeonAbilitySystemComponent.generated.h"

struct FAeonGameplayAbilitySet;

/** The AbilitySystemComponent specialization used in Aeon */
UCLASS()
class AEON_API UAeonAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    /**
     * Callback invoked when an AbilityInputAction has associated Input pressed.
     *
     * @param InTag The InputTag that identifies the ability.
     * @see UAeonInputConfig for where AbilityInputAction are defined
     */
    void OnAbilityInputPressed(const FGameplayTag& InTag);

    /**
     * Callback invoked when an AbilityInputAction has associated Input released.
     *
     * @param InTag The InputTag that identifies the ability.
     * @see UAeonInputConfig for where AbilityInputAction are defined
     */
    void OnAbilityInputReleased(const FGameplayTag& InTag);

    /**
     * Grant the specified abilities
     *
     * @param InAbilities the abilities to grant.
     * @param InApplyLevel the level at which to grant abilities.
     * @param OutGrantedAbilitySpecHandles the spec handles of the granted abilities.
     */
    UFUNCTION(BlueprintCallable, Category = "Aeon|Ability", meta = (InApplyLevel = "1"))
    void GrantHeroWeaponAbilities(const TArray<FAeonGameplayAbilitySet>& InAbilities,
                                  int32 InApplyLevel,
                                  TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

    /**
     * Remove abilities specified by the ability handles.
     *
     * @param InAbilitySpecHandles The AbilityHandles to clear.
     */
    UFUNCTION(BlueprintCallable, Category = "Aeon|Ability")
    void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) const TArray<FGameplayAbilitySpecHandle>& InAbilitySpecHandles);
};
