#include "AbilitySystem/Abilities/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/Attributes/WarriorAttributeSet.h"
#include "WarriorGameplayTags.h"

struct FWarriorDamageCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

    FWarriorDamageCapture()
    {
        // Captures the Attack power from the source
        DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false)
        // Captures the Defense power from the target
        DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefensePower, Target, false)
        // Captures the Damage Taken from the target
        DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DamageTaken, Target, false)
    }
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
    static const FWarriorDamageCapture WarriorDamageCapture;
    return WarriorDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
    RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
    RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);
    RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const auto& EffectSpec = ExecutionParams.GetOwningSpec();

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    // ---------------------------------------------------------
    // Retrieve the captured attributes from source/target
    // ---------------------------------------------------------

    float SourceAttackPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef,
                                                               EvaluateParameters,
                                                               SourceAttackPower);
    float TargetDefensePower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef,
                                                               EvaluateParameters,
                                                               TargetDefensePower);

    // ---------------------------------------------------------
    // Retrieve the properties passed to effect via the
    // SetByCaller infrastructure
    // ---------------------------------------------------------

    float BaseDamage = 0.f;
    int32 LightAttackComboLevel = 0;
    int32 HeavyAttackComboLevel = 0;

    for (const auto& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
    {
        if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage))
        {
            BaseDamage = TagMagnitude.Value;
        }
        else if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light))
        {
            LightAttackComboLevel = TagMagnitude.Value;
        }
        else if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy))
        {
            HeavyAttackComboLevel = TagMagnitude.Value;
        }
    }

    // ---------------------------------------------------------
    // Calculate the Final Damage
    // ---------------------------------------------------------

    if (0 != LightAttackComboLevel)
    {
        // Scale damage so that higher combo levels do greater damage
        BaseDamage *= (LightAttackComboLevel - 1) * 0.05f + 1.f;
    }

    if (0 != HeavyAttackComboLevel)
    {
        // Scale damage so that higher combo levels do greater damage
        BaseDamage *= HeavyAttackComboLevel * 0.15f + 1.f;
    }

    // ReSharper disable once CppTooWideScopeInitStatement
    const float DamageTaken = BaseDamage * SourceAttackPower / TargetDefensePower;

    // ---------------------------------------------------------
    // Update DamageTake if required
    // ---------------------------------------------------------

    if (DamageTaken > 0.f)
    {
        // We set the DamageTaken to calculated damage
        // NOTE: We do not directly remove it from Health as setting
        OutExecutionOutput.AddOutputModifier(
            FGameplayModifierEvaluatedData(GetWarriorDamageCapture().DamageTakenProperty,
                                           EGameplayModOp::Override,
                                           DamageTaken));
    }
}
