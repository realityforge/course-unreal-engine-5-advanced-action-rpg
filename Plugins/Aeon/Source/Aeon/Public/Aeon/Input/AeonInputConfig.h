#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AeonInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * Association of a Input.Native subtag to an InputAction.
 */
USTRUCT(BlueprintType)
struct FAeonNativeInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input.Native"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> InputAction{ nullptr };

    bool IsValid() const { return InputTag.IsValid() && InputAction; }
};

/**
 * Association of a Input.Ability subtag to an InputAction.
 */
USTRUCT(BlueprintType)
struct FAeonAbilityInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input.Ability"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> InputAction{ nullptr };

    bool IsValid() const { return InputTag.IsValid() && InputAction; }
};

/**
 * DataAsset containing InputAction to GameplayTag configuration.
 */
UCLASS()
class AEON_API UAeonInputConfig : public UDataAsset
{
    GENERATED_BODY()

    /**
     * The Default MappingContext applied to when using config.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    /**
     * A set of "well-know" tags that are bound to the InputAction.
     * These are manually bound.
     * The callbacks all take a FInputActionValue reference parameter.
     * The supported tags are those with the prefix "Input.Native."
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag", AllowPrivateAccess = "true"))
    TArray<FAeonNativeInputAction> NativeInputActions;

    /**
     * A set of tags that are bound to InputAction.
     * The callbacks all take a FGameplayTag parameter.
     * The supported tags are those with the prefix "Input.Ability."
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag", AllowPrivateAccess = "true"))
    TArray<FAeonAbilityInputAction> AbilityInputActions;

public:
    /**
     * Return the InputAction registered with the specified Tag.
     *
     * @param InInputTag the InputTag to look for.
     * @return the InputAction, if present.
     */
    UFUNCTION(BlueprintCallable, Category = "Aeon|Input")
    const UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;

    FORCEINLINE const TArray<FAeonAbilityInputAction>& GetAbilityInputActions() const { return AbilityInputActions; };
    FORCEINLINE UInputMappingContext* GetDefaultMappingContext() const { return DefaultMappingContext; };
};
