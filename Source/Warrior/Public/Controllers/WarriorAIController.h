#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "WarriorAIController.generated.h"

/**
 * Base class for AI controllers in the warrior project.
 */
UCLASS(Abstract)
class WARRIOR_API AWarriorAIController : public AAIController
{
    GENERATED_BODY()

public:
    explicit AWarriorAIController(const FObjectInitializer& ObjectInitializer);
};
