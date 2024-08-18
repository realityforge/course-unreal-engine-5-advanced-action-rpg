#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AeonGameplayAbilitySet.generated.h"

class UAeonGameplayAbility;

/**
 * Definition of a GameplayAbility that can be granted to Actor.
 */
USTRUCT(BlueprintType)
struct AEON_API FAeonGameplayAbilitySet
{
    GENERATED_BODY()

    /** Tag via which the actor can trigger the Ability. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input"))
    FGameplayTag InputTag;

    // TODO: It is unclear why the ApplyLevel is not configured here rather than jury rigged in at a later stage.

    /** The Ability. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UAeonGameplayAbility> Ability;

    bool IsValid() const;
};
