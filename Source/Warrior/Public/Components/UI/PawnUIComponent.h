#pragma once
#include "Aeon/Components/AeonPawnComponentBase.h"
#include "CoreMinimal.h"
#include "PawnUIComponent.generated.h"

/**
 * Abstract component with UI related functionality that is shared between the Hero/Enemy classes.
 */
UCLASS(Abstract)
class WARRIOR_API UPawnUIComponent : public UAeonPawnComponentBase
{
    GENERATED_BODY()
};
