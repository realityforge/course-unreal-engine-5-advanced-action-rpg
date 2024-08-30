#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorFunctionLibrary.generated.h"

struct FGameplayTag;
class UAeonAbilitySystemComponent;

UENUM()
enum class EWarriorConfirmType : uint8
{
    Yes,
    No
};

/**
 * Blueprint function library exposing useful functions used within this project.
 */
UCLASS()
class WARRIOR_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary

{
    GENERATED_BODY()

public:
    static UAeonAbilitySystemComponent* NativeGetAeonAbilitySystemComponentFromActor(AActor* InActor);

    UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
    static void AddGameplayTagToActorIfNotPresent(AActor* InActor, FGameplayTag InGameplayTag);

    UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
    static void RemoveGameplayTagFromActorIfPresent(AActor* InActor, FGameplayTag InGameplayTag);

    static bool NativeIsGameplayTagPresentOnActor(AActor* InActor, FGameplayTag InGameplayTag);

    UFUNCTION(BlueprintCallable,
              Category = "Warrior|FunctionLibrary",
              meta = (DisplayName = "Is GameplayTag Present On Actor", ExpandEnumAsExecs = "OutConfirmType"))
    static void
    BP_IsGameplayTagPresentOnActor(AActor* InActor, FGameplayTag InGameplayTag, EWarriorConfirmType& OutConfirmType);
};
