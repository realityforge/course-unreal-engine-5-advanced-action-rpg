#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "EnhancedInputComponent.h"
#include "WarriorInputComponent.generated.h"

struct FGameplayTag;

/**
 *
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    template <class UserObject, typename CallbackFunc>
    void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
                               const FGameplayTag& InInputTag,
                               ETriggerEvent TriggerEvent,
                               UserObject* ContextObject,
                               CallbackFunc Func);
};

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                   const FGameplayTag& InInputTag,
                                                   ETriggerEvent TriggerEvent,
                                                   UserObject* ContextObject,
                                                   CallbackFunc Func)
{
    checkf(InInputConfig, TEXT("InputConfig data asset is null, Binding not valid"));
    if (const auto Action = InInputConfig->FindNativeInputActionByTag(InInputTag))
    {
        BindAction(Action, TriggerEvent, ContextObject, Func);
    }
}
