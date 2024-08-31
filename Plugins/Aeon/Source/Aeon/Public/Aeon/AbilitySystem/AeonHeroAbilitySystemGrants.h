#pragma once

#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "CoreMinimal.h"
#include "AeonHeroAbilitySystemGrants.generated.h"

struct FAeonGameplayAbilitySet;

UCLASS()
class AEON_API UAeonHeroAbilitySystemGrants : public UAeonAbilitySystemGrantsBase
{
    GENERATED_BODY()

    /** Abilities that are granted to the actor at startup. */
    UPROPERTY(EditDefaultsOnly,
              Category = "Aeon|StartUpData",
              meta = (AllowAbstract = "false", TitleProperty = "InputTag"))
    TArray<FAeonGameplayAbilitySet> StartUpAbilitySets;

public:
    virtual void GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel) override;
};
