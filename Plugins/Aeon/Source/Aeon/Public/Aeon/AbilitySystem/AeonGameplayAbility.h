#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"
#include "AeonGameplayAbility.generated.h"

class UWarriorAbilitySystemComponent;
class UPawnCombatComponent;

/**
 * Strategy that the GameplayAbility uses to activate.
 */
UENUM(BlueprintType)
enum class EAeonAbilityActivationPolicy : uint8
{
    OnTriggered,

    // Activate the ability when it is given to the Avatar
    OnGiven
};

/**
 * The base GameplayAbility class used by Aeon.
 */
UCLASS(Abstract)
class AEON_API UAeonGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Aeon|Ability")
    EAeonAbilityActivationPolicy AbilityActivationPolicy{ EAeonAbilityActivationPolicy::OnTriggered };

protected:
    //~Begin UGameplayAbility Interface
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
                            const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo,
                            bool bReplicateEndAbility,
                            bool bWasCancelled) override;
    //~End UGameplayAbility Interface

public:
    //~Begin UGameplayAbility Interface
    virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    //~End UGameplayAbility Interface
};
