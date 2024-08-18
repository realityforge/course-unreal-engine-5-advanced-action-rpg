#pragma once

#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "CoreMinimal.h"
#include "AeonHeroAbilitySystemGrants.generated.h"

struct FAeonGameplayAbilitySet;

// TODO: It is unclear why we can not merge this with UAeonAbilitySystemGrantsBase
// TODO: It is unclear why we have multiple AbilitySet arrays given the AbilityActivationPolicy is part of ability and
// we could just merge Keeping it all as is now to follow tutorial. Can potentially come back and refactor at a later
// date

UCLASS()
class AEON_API UAeonHeroAbilitySystemGrants : public UAeonAbilitySystemGrantsBase
{
    GENERATED_BODY()

    /** Abilities that are granted to the hero at startup. */
    UPROPERTY(EditDefaultsOnly,
              Category = "Aeon|StartUpData",
              meta = (AllowAbstract = "false", TitleProperty = "InputTag"))
    TArray<FAeonGameplayAbilitySet> StartUpAbilitySets;

public:
    virtual void GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel) override;
};
