#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarriorCharacterBase.generated.h"

class UAeonAbilitySystemGrantsBase;
class UWarriorAttributeSet;
class UAeonAbilitySystemComponent;

UCLASS()
class WARRIOR_API AWarriorCharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Warrior|Ability", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAeonAbilitySystemComponent> AeonAbilitySystemComponent{ nullptr };

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Warrior|AbilitySystem",
              meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWarriorAttributeSet> WarriorAttributeSet{ nullptr };

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "CharacterData",
              meta = (AllowPrivateAccess = "true", RuleRangerRequired = "true"))
    TSoftObjectPtr<UAeonAbilitySystemGrantsBase> CharacterStartUpData{ nullptr };

protected:
    void GiveStartUpDataToAbilitySystem() const;

public:
    AWarriorCharacterBase();

    virtual void PossessedBy(AController* NewController) override;

    //~ Begin IAbilitySystemInterface Interface.
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //~ End IAbilitySystemInterface Interface

    FORCEINLINE UAeonAbilitySystemComponent* GetAeonAbilitySystemComponent() const
    {
        return AeonAbilitySystemComponent;
    }

    FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
