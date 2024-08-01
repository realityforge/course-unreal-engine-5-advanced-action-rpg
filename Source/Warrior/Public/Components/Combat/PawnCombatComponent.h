#pragma once

#include "Components/PawnExtensionComponentBase.h"
#include "CoreMinimal.h"
#include "PawnCombatComponent.generated.h"

/**
 * Abstract component with combat related functionality that is shared between the Hero/Enemy classes.
 */
UCLASS(Abstract)
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
    GENERATED_BODY()
};
