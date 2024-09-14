#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_DamageTaken.generated.h"

/**
 * Calculates the DamageTaken attribute.
 * The damage is calculated based on the BaseDamage of weapon, attack type (Light/Heavy) and ComboLevel.
 * These are passed with EffectSpec via SetByCaller parameters.
 * The calculation is modified by the ratio of the initiator "AttackPower" and the targets "DefensePower".
 */
UCLASS()
class WARRIOR_API UGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:
    UGEExecCalc_DamageTaken();

    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
