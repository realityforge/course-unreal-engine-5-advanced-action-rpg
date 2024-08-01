#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;

UCLASS(Abstract)
class WARRIOR_API UDataAsset_StartUpDataBase : public UDataAsset
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (AllowAbstract = "false"))
    TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (AllowAbstract = "false"))
    TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

    void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InGameplayAbilities,
                        UWarriorAbilitySystemComponent* InAbilitySystemComponent,
                        int32 ApplyLevel);

public:
    virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel = 1);
};
