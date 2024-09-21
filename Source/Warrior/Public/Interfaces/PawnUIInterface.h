#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UPawnUIComponent;
class UHeroUIComponent;
class UEnemyUIComponent;

UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
    GENERATED_BODY()
};

class WARRIOR_API IPawnUIInterface
{
    GENERATED_BODY()

public:
    virtual UPawnUIComponent* GetPawnUIComponent() const = 0;
};
