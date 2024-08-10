#pragma once

#include "AnimInstances/WarriorAnimInstanceBase.h"
#include "CoreMinimal.h"
#include "WarriorHeroLinkedAnimLayer.generated.h"

class UWarriorHeroAnimInstance;

UCLASS()
class WARRIOR_API UWarriorHeroLinkedAnimLayer : public UWarriorAnimInstanceBase
{
    GENERATED_BODY()

public:
    // MUST be both Pure and ThreadSafe to be accessible in Layer AnimGraph

    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    UWarriorHeroAnimInstance* GetHeroAnimInstance() const;
};
