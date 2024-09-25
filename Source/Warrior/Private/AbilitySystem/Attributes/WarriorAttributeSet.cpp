#include "AbilitySystem/Attributes/WarriorAttributeSet.h"
#include "Components/UI/HeroUIComponent.h"
#include "Components/UI/PawnUIComponent.h"
#include "GameplayEffectExtension.h"
#include "Interfaces/PawnUIInterface.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"

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
    AActor* TargetAvatarActor = Data.Target.GetAvatarActor();
    if (!CachedPawnUIInterface.IsValid())
    {
        // Get the Avatar Actor from the "owner"/Ability System Component Target
        CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(TargetAvatarActor);
    }
    const bool bCachedPawnUIInterfaceValid = ensureAlwaysMsgf(CachedPawnUIInterface.IsValid(),
                                                              TEXT("Expected Actor %s to implement IPawnUIInterface"),

                                                              *TargetAvatarActor->GetActorNameOrLabel());
    const UPawnUIComponent* PawnUIComponent{ nullptr };
    if (bCachedPawnUIInterfaceValid)
    {
        PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
        checkf(PawnUIComponent,
               TEXT("Actor named %s returned nullptr for GetPawnUIComponent()"),
               *TargetAvatarActor->GetActorNameOrLabel())
    }

    if (GetCurrentHealthAttribute() == Data.EvaluatedData.Attribute)
    {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
        if (PawnUIComponent)
        {
            PawnUIComponent->GetOnCurrentHealthChanged().Broadcast(GetCurrentHealth() / GetMaxHealth());
        }
    }
    else if (GetCurrentRageAttribute() == Data.EvaluatedData.Attribute)
    {
        SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));
        if (const auto HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
        {
            HeroUIComponent->GetOnCurrentRageChanged().Broadcast(GetCurrentRage() / GetMaxRage());
        }
    }
    else if (GetDamageTakenAttribute() == Data.EvaluatedData.Attribute)
    {
        if (const float CurrentDamageTaken = GetDamageTaken(); 0.f != CurrentDamageTaken)
        {
            SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - CurrentDamageTaken, 0.f, GetMaxHealth()));

            // TODO: Update UI?

            if (0.f == GetCurrentHealth())
            {
                UWarriorFunctionLibrary::AddGameplayTagToActorIfNotPresent(TargetAvatarActor,
                                                                           WarriorGameplayTags::Shared_Status_Dead);
            }
            SetDamageTaken(0.f);
        }
    }
}
