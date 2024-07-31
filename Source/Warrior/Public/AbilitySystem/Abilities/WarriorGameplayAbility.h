

#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"
#include "WarriorGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8
{
    OnTriggered,
    OnGiven
};

UCLASS()
class WARRIOR_API UWarriorGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "WarriorAbility")
    EWarriorAbilityActivationPolicy AbilityActivationPolicy{ EWarriorAbilityActivationPolicy::OnTriggered };

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
