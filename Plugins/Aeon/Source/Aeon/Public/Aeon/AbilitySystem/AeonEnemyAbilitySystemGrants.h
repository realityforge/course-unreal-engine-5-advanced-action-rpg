#pragma once

#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "CoreMinimal.h"
#include "AeonEnemyAbilitySystemGrants.generated.h"

struct FAeonGameplayAbilitySet;

UCLASS()
class AEON_API UAeonEnemyAbilitySystemGrants : public UAeonAbilitySystemGrantsBase
{
    GENERATED_BODY()

    /** Abilities that are granted to the actor at startup. */
    UPROPERTY(EditDefaultsOnly,
              Category = "Aeon|StartUpData",
              meta = (AllowAbstract = "false", TitleProperty = "InputTag"))
    TArray<TSubclassOf<UAeonGameplayAbility>> StartUpAbilities;

public:
    virtual void GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel) override;
};
