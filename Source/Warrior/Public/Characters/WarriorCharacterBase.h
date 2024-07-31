#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarriorCharacterBase.generated.h"

class UWarriorAttributeSet;
class UWarriorAbilitySystemComponent;

UCLASS()
class WARRIOR_API AWarriorCharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

    // Set up folding Region for VS
#pragma region Components

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWarriorAbilitySystemComponent> WarriorAbilitySystemComponent{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWarriorAttributeSet> WarriorAttributeSet{ nullptr };

#pragma endregion

public:
    AWarriorCharacterBase();

    //~ Begin AActor Interface.
    virtual void PostInitializeComponents() override;
    //~ End AActor Interface

    //~ Begin IAbilitySystemInterface Interface.
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //~ End IAbilitySystemInterface Interface

    FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const
    {
        return WarriorAbilitySystemComponent;
    }

    FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
