#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AeonGameModeBase.generated.h"

/**
 * The base game mode in Aeon.
 */
UCLASS(Abstract, meta = (ShortTooltip = "The base game mode class used in Aeon."))
class AEON_API AAeonGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
};
