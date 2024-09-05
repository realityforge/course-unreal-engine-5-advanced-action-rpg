#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AeonAbilitySystemGrantsBase.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UAeonGameplayAbility;
class UAeonAbilitySystemComponent;

// TODO: This should have the functionality present in AeonEnemyAbilitySystemGrants and AeonHeroAbilitySystemGrants
//       merged into the class. Keeping it separate until the end of the course and we can refactor later.
// TODO: It is unclear why we have multiple AbilitySet arrays given the AbilityActivationPolicy is part of ability and
//       we could just merge. Keeping it all as is now to follow tutorial. Can refactor later.
// TODO: We should introduce a structure so that GameplayAbility and ApplyLevel are colocated (as well as potentially a
// identifying tag and/or input tag)

/**
 * Abstract DataAsset that describes abilities that can be granted to an actor.
 */
UCLASS(Abstract)
class AEON_API UAeonAbilitySystemGrantsBase : public UDataAsset
{
    GENERATED_BODY()

    /** Activities that are granted to the actor and immediately activated. */
    UPROPERTY(EditDefaultsOnly, Category = "Aeon|StartUpData", meta = (AllowAbstract = "false"))
    TArray<TSubclassOf<UGameplayAbility>> ActivateOnGivenAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "Aeon|StartUpData", meta = (AllowAbstract = "false"))
    TArray<TSubclassOf<UGameplayAbility>> ReactiveAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "Aeon|StartUpData", meta = (AllowAbstract = "false", BlueprintBaseOnly))
    TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

protected:
    void GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities,
                        UAeonAbilitySystemComponent* InAbilitySystemComponent,
                        int32 ApplyLevel) const;

    void GrantEffects(const TArray<TSubclassOf<UGameplayEffect>>& InGameplayEffects,
                      UAeonAbilitySystemComponent* InAbilitySystemComponent,
                      const int32 ApplyLevel) const;

public:
    virtual void GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel = 1);
};
