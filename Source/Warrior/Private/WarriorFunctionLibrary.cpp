#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"

UAeonAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetAeonAbilitySystemComponentFromActor(AActor* InActor)
{
    checkf(InActor, TEXT("InActor passed as NULL"));

    return CastChecked<UAeonAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNotPresent(AActor* InActor, const FGameplayTag InGameplayTag)
{
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AbilitySystemComponent = NativeGetAeonAbilitySystemComponentFromActor(InActor);
    if (!AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag))
    {
        AbilitySystemComponent->AddLooseGameplayTag(InGameplayTag);
    }
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfPresent(AActor* InActor, const FGameplayTag InGameplayTag)
{
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AbilitySystemComponent = NativeGetAeonAbilitySystemComponentFromActor(InActor);
    if (AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag))
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(InGameplayTag);
    }
}

bool UWarriorFunctionLibrary::NativeIsGameplayTagPresentOnActor(AActor* InActor, const FGameplayTag InGameplayTag)
{
    return NativeGetAeonAbilitySystemComponentFromActor(InActor)->HasMatchingGameplayTag(InGameplayTag);
}

void UWarriorFunctionLibrary::BP_IsGameplayTagPresentOnActor(AActor* InActor,
                                                             const FGameplayTag InGameplayTag,
                                                             EWarriorConfirmType& OutConfirmType)
{
    OutConfirmType =
        NativeIsGameplayTagPresentOnActor(InActor, InGameplayTag) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}
