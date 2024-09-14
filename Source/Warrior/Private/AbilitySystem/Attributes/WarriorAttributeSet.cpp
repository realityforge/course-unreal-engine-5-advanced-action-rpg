#include "AbilitySystem/Attributes/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
    InitCurrentHealth(1.f);
    InitMaxHealth(1.f);
    InitCurrentRage(1.f);
    InitMaxRage(1.f);
    InitAttackPower(1.f);
    InitDefensePower(1.f);
    InitDamageTaken(0.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    if (GetCurrentHealthAttribute() == Data.EvaluatedData.Attribute)
    {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
        // TODO: Update UI?
    }
    else if (GetCurrentRageAttribute() == Data.EvaluatedData.Attribute)
    {
        SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));
        // TODO: Update UI?
    }
    else if (GetDamageTakenAttribute() == Data.EvaluatedData.Attribute)
    {
        if (const float CurrentDamageTaken = GetDamageTaken(); 0.f != CurrentDamageTaken)
        {
            SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - CurrentDamageTaken, 0.f, GetMaxHealth()));

            // TODO: Update UI?

            if (0.f == GetCurrentHealth())
            {
                // TODO: Handle Character Death
            }
            SetDamageTaken(0.f);
        }
    }
}
