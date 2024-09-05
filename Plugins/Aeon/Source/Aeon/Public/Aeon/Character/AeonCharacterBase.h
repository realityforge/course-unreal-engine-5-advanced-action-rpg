#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AeonCharacterBase.generated.h"

class UAeonAttributeSet;
class UAeonAbilitySystemGrantsBase;
class UAeonAbilitySystemComponent;

UCLASS(Abstract, meta = (ShortTooltip = "The base character class used by Aeon."))
class AEON_API AAeonCharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aeon|Ability", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAeonAbilitySystemComponent> AeonAbilitySystemComponent{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aeon|AbilitySystem", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAeonAttributeSet> AeonAttributeSet{ nullptr };

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "Aeon|AbilitySystem",
              meta = (AllowPrivateAccess = "true", RuleRangerRequired = "true"))
    TSoftObjectPtr<UAeonAbilitySystemGrantsBase> CharacterStartUpData{ nullptr };

protected:
    void GiveStartUpDataToAbilitySystem() const;
    void GiveStartUpDataToAbilitySystemAsync() const;

    void InitAbilityActorInfo();

public:
    AAeonCharacterBase();

    //~ Begin IAbilitySystemInterface Interface.
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //~ End IAbilitySystemInterface Interface

    FORCEINLINE UAeonAbilitySystemComponent* GetAeonAbilitySystemComponent() const
    {
        return AeonAbilitySystemComponent;
    }

    FORCEINLINE UAeonAttributeSet* GetAeonAttributeSet() const { return AeonAttributeSet; }
};
