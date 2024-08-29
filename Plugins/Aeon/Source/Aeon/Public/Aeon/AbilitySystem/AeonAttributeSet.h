#pragma once

#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "AeonAttributeSet.generated.h"

/**
 * The base AttributeSet in Aeon.
 */
UCLASS(Abstract, meta = (ShortTooltip = "The base AttributeSet used in Aeon."))
class AEON_API UAeonAttributeSet : public UAttributeSet
{
    GENERATED_BODY()
};
