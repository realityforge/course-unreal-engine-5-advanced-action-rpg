#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AeonAbilitySystemGrantsBase.generated.h"

class UGameplayAbility;
class UAeonGameplayAbility;
class UAeonAbilitySystemComponent;

/**
 * Abstract DataAsset that describes abilities that can be granted to an actor.
 */
UCLASS(Abstract)
class AEON_API UAeonAbilitySystemGrantsBase : public UDataAsset
{
    GENERATED_BODY()

    /** Activities that are granted to the actor and immediately activated. */
    UPROPERTY(EditDefaultsOnly, Category = "Aeon|StartUpData", meta = (AllowAbstract = "false"))
    TArray<TSubclassOf<UGameplayAbility>> ActivateOnGivenAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "Aeon|StartUpData", meta = (AllowAbstract = "false"))
    TArray<TSubclassOf<UGameplayAbility>> ReactiveAbilities;

protected:
    void GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities,
                        UAeonAbilitySystemComponent* InAbilitySystemComponent,
                        int32 ApplyLevel);

public:
    virtual void GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                              int32 ApplyLevel = 1);
};
