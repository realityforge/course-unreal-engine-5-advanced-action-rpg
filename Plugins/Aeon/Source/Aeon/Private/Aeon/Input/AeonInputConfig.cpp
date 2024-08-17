#include "Aeon/Input/AeonInputConfig.h"

const UInputAction* UAeonInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
    for (const auto& [InputTag, InputAction] : NativeInputActions)
    {
        if (InputTag == InInputTag && InputAction)
        {
            return InputAction;
        }
    }
    return nullptr;
}
