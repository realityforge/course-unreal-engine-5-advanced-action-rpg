#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> InputAction;

    bool IsValid() const { return InputTag.IsValid() && InputAction; }
};

/**
 *
 */
UCLASS()
class WARRIOR_API UDataAsset_InputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    /**
     * A set of "well-know" tags that are bound to InputAction.
     * The callbacks all take a FInputActionValue reference parameter.
     * The supported tags are those with the prefix "Input.Native."
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FWarriorInputActionConfig> NativeInputActions;

    /**
     * A set of tags that are bound to InputAction.
     * The callbacks all take a FGameplayTag parameter.
     * The supported tags are those with the prefix "Input.Ability."
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
    TArray<FWarriorInputActionConfig> AbilityInputActions;

    UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
