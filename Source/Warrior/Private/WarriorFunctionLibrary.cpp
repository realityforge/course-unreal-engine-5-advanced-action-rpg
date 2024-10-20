#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/Logging.h"
#include "GenericTeamAgentInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "WarriorGameplayTags.h"

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

FGameplayTag UWarriorFunctionLibrary::ComputeHitReactDirectionTag(const AActor* Attacker,
                                                                  const AActor* Victim,
                                                                  float& AngleDifference)
{
    if (ensureAlwaysMsgf(Attacker, TEXT("Null Attacker supplied to function")))
    {
        if (ensureAlwaysMsgf(Victim, TEXT("Null Victim supplied to function")))
        {
            const FVector VictimForward = Victim->GetActorForwardVector();
            const FVector VictimToAttackerNormalized =
                (Attacker->GetActorLocation() - Victim->GetActorLocation()).GetSafeNormal();

            // Factor determines whether the angle between victim is to the right or to the left.
            // Unreal is RHS system, so when the second vector is on the right of the first vector,
            // then the cross-product points up
            const float Factor = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized).Z >= 0.f ? 1.f : -1.f;

            AngleDifference =
                UKismetMathLibrary::DegAcos(FVector::DotProduct(VictimForward, VictimToAttackerNormalized)) * Factor;
            if (AngleDifference >= -45.f && AngleDifference <= 45.f)
            {
                return WarriorGameplayTags::Shared_Status_HitReact_Front;
            }
            else if (AngleDifference < -45.f && AngleDifference >= -135.f)
            {
                return WarriorGameplayTags::Shared_Status_HitReact_Left;
            }
            else if (AngleDifference < -135.f || AngleDifference > 135.f)
            {
                return WarriorGameplayTags::Shared_Status_HitReact_Back;
            }
            else if (AngleDifference > 45.f && AngleDifference <= 135.f)
            {
                return WarriorGameplayTags::Shared_Status_HitReact_Right;
            }
            else
            {
                return WarriorGameplayTags::Shared_Status_HitReact_Front;
            }
        }
    };
    return WarriorGameplayTags::Shared_Status_HitReact_Front;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
                                                                                  EWarriorValidType& OutValidType)
{
    const auto CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
    OutValidType = CombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;
    return CombatComponent;
}
