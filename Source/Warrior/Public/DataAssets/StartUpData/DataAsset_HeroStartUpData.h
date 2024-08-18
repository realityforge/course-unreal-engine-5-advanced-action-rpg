#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"

UCLASS()
class WARRIOR_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
    GENERATED_BODY()

    /** Abilities that are granted to the hero at startup. */
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (AllowAbstract = "false", TitleProperty = "InputTag"))
    TArray<FAeonGameplayAbilitySet> StartUpAbilitySets;

public:
    virtual void GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel) override;
};
