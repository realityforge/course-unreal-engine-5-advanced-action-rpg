#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
    GENERATED_BODY()

    /** Tag to identify the Ability. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag Tag;

    /** The Ability. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UWarriorGameplayAbility> Ability;

    bool IsValid() const;
};

UCLASS()
class WARRIOR_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
    GENERATED_BODY()

    /** Abilities that are granted to the hero at startup. */
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (AllowAbstract = "false", TitleProperty = "Tag"))
    TArray<FWarriorHeroAbilitySet> StartUpAbilitySets;

public:
    virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel) override;
};
