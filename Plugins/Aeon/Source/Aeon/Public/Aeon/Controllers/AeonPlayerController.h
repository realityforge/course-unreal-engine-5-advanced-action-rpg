#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AeonPlayerController.generated.h"

/**
 * The base player controller used by Aeon.
 */
UCLASS(meta = (ShortTooltip = "The base player controller class used by Aeon."))
class AEON_API AAeonPlayerController : public APlayerController
{
    GENERATED_BODY()
};
