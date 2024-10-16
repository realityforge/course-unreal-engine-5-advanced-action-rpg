#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/Logging.h"
#include "GenericTeamAgentInterface.h"
#include "Interfaces/PawnCombatInterface.h"

UAeonAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetAeonAbilitySystemComponentFromActor(AActor* InActor)
{
    checkf(InActor, TEXT("InActor passed as NULL"));

    return CastChecked<UAeonAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNotPresent(AActor* InActor, const FGameplayTag InGameplayTag)
{
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor);
    if (!AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag))
    {
        AbilitySystemComponent->AddLooseGameplayTag(InGameplayTag);
    }
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfPresent(AActor* InActor, const FGameplayTag InGameplayTag)
{
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor);
    if (AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag))
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(InGameplayTag);
    }
}

bool UWarriorFunctionLibrary::NativeIsGameplayTagPresentOnActor(AActor* InActor, const FGameplayTag InGameplayTag)
{
    return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor)->HasMatchingGameplayTag(InGameplayTag);
}

void UWarriorFunctionLibrary::BP_IsGameplayTagPresentOnActor(AActor* InActor,
                                                             const FGameplayTag InGameplayTag,
                                                             EWarriorConfirmType& OutConfirmType)
{
    OutConfirmType =
        NativeIsGameplayTagPresentOnActor(InActor, InGameplayTag) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
    checkf(InActor, TEXT("InActor passed as NULL"));

    const auto CombatInterface = Cast<IPawnCombatInterface>(InActor);
    return CombatInterface ? CombatInterface->GetPawnCombatComponent() : nullptr;
}

bool UWarriorFunctionLibrary::IsTargetPawnHostile(const APawn* Pawn, const APawn* TargetPawn)
{
    if (!Pawn)
    {
        AEON_WARNING_ALOG("UWarriorFunctionLibrary::IsTargetPawnHostile - Passed in NULL Pawn parameter")
        return false;
    }
    else if (!TargetPawn)
    {
        AEON_WARNING_ALOG("UWarriorFunctionLibrary::IsTargetPawnHostile - Passed in NULL TargetPawn parameter")
        return false;
    }
    else
    {
        const auto PawnTeamAgent = Cast<IGenericTeamAgentInterface>(Pawn->GetController());
        const auto TargetPawnTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
        return PawnTeamAgent && TargetPawnTeamAgent
            ? PawnTeamAgent->GetGenericTeamId() != TargetPawnTeamAgent->GetGenericTeamId()
            : false;
    }
}

float UWarriorFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& ScalableFloat, float Level)
{
    return ScalableFloat.GetValueAtLevel(Level);
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
                                                                                  EWarriorValidType& OutValidType)
{
    const auto CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
    OutValidType = CombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;
    return CombatComponent;
}
