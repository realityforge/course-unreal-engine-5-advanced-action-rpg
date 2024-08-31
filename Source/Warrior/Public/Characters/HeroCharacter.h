#pragma once

#include "Characters/WarriorCharacterBase.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HeroCharacter.generated.h"

class UHeroCombatComponent;
struct FInputActionValue;
class UAeonInputConfig;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Abstract)
class WARRIOR_API AHeroCharacter : public AWarriorCharacterBase
{
    GENERATED_BODY()

#pragma region Components

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UHeroCombatComponent> CombatComponent;

#pragma endregion

#pragma region Inputs

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "CharacterData",
              meta = (AllowPrivateAccess = "true", RuleRangerRequired = "true"))
    TObjectPtr<UAeonInputConfig> InputConfigDataAsset;

    void Input_Move(const FInputActionValue& InputActionValue);

    void Input_Look(const FInputActionValue& InputActionValue);

    void Input_AbilityInputPressed(const FGameplayTag InGameplayTag);
    void Input_AbilityInputReleased(const FGameplayTag InGameplayTag);

#pragma endregion

protected:
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
    AHeroCharacter();

    virtual void PossessedBy(AController* NewController) override;

    FORCEINLINE UHeroCombatComponent* GetCombatComponent() const { return CombatComponent; }
};
