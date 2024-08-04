#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "WarriorAbilitySystemComponent.generated.h"

UCLASS()
class WARRIOR_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    void OnAbilityInputPressed(const FGameplayTag& InTag);
    void OnAbilityInputReleased(const FGameplayTag& InTag);
};
