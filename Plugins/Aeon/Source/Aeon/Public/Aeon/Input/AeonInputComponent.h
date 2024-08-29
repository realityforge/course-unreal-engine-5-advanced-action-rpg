#pragma once

#include "Aeon/Input/AeonInputConfig.h"
#include "Aeon/Logging.h"
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AeonInputComponent.generated.h"

struct FGameplayTag;

/**
 * An EnhancedInputComponent derived class that binds input using an AeonInputConfig asset.
 *
 * The class just adds functions to simplify the binding using an AeonInputConfig asset and this could be replaced
 * by macros or helper functions in the caller class. However, this class is retained for ease of use.
 */
UCLASS(
    meta = (ShortTooltip = "An EnhancedInputComponent derived class that binds input using an AeonInputConfig asset."))
class AEON_API UAeonInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    template <class UserObject, typename CallbackFunc>
    void BindNativeInputAction(const UAeonInputConfig* InInputConfig,
                               const FGameplayTag& InInputTag,
                               ETriggerEvent TriggerEvent,
                               UserObject* ContextObject,
                               CallbackFunc Func);

    template <class UserObject, typename CallbackFunc>
    void BindAbilityInputAction(const UAeonInputConfig* InInputConfig,
                                UserObject* ContextObject,
                                CallbackFunc InputPressedFunc,
                                CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UAeonInputComponent::BindNativeInputAction(const UAeonInputConfig* InInputConfig,
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
void UAeonInputComponent::BindAbilityInputAction(const UAeonInputConfig* InInputConfig,
                                                 UserObject* ContextObject,
                                                 CallbackFunc InputPressedFunc,
                                                 CallbackFunc InputReleasedFunc)
{
    checkf(InInputConfig, TEXT("InputConfig data asset is null, Binding not valid"));
    for (const auto Action : InInputConfig->GetAbilityInputActions())
    {
        if (Action.IsValid())
        {
            BindAction(Action.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, Action.InputTag);
            BindAction(Action.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, Action.InputTag);
        }
        else
        {
            AEON_ERROR_ALOG("BindAbilityInputAction: Invalid Action in InputConfig with InputTag %s and Action %s",
                            *Action.InputTag.ToString(),
                            IsValid(Action.InputAction) ? *Action.InputAction.GetFullName() : TEXT("?"));
        }
    }
}
