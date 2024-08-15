#pragma once

#include "Aeon/Logging.h"
#include "CoreMinimal.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "EnhancedInputComponent.h"
#include "WarriorInputComponent.generated.h"

struct FGameplayTag;

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

    template <class UserObject, typename CallbackFunc>
    void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
                                UserObject* ContextObject,
                                CallbackFunc InputPressedFunc,
                                CallbackFunc InputReleasedFunc);
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
    else
    {
        AEON_WARNING_ALOG("BindNativeInputAction: Unable to locate InputAction with InputTag %s",
                          *InInputTag.ToString());
    }
}

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                    UserObject* ContextObject,
                                                    CallbackFunc InputPressedFunc,
                                                    CallbackFunc InputReleasedFunc)
{
    checkf(InInputConfig, TEXT("InputConfig data asset is null, Binding not valid"));
    for (const auto Action : InInputConfig->AbilityInputActions)
    {
        if (Action.IsValid())
        {
            BindAction(Action.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, Action.Tag);
            BindAction(Action.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, Action.Tag);
        }
        else
        {
            AEON_ERROR_ALOG("BindAbilityInputAction: Invalid Action in InputConfig with InputTag %s and Action %s",
                            *Action.Tag.ToString(),
                            IsValid(Action.InputAction) ? *Action.InputAction.GetFullName() : TEXT("?"));
        }
    }
}
