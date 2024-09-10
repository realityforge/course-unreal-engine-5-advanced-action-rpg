#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnCombatInterface.generated.h"

class UPawnCombatComponent;

UINTERFACE(MinimalAPI)
class UPawnCombatInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * The interface that can be used to get access to the PawnCombatComponent.
 */
class WARRIOR_API IPawnCombatInterface
{
    GENERATED_BODY()

public:
    virtual UPawnCombatComponent* GetPawnCombatComponent() const = 0;
};
