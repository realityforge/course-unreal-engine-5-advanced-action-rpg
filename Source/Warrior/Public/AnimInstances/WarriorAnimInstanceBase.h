#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "WarriorAnimInstanceBase.generated.h"

struct FGameplayTag;

UCLASS(Abstract)
class WARRIOR_API UWarriorAnimInstanceBase : public UAnimInstance
{
    GENERATED_BODY()

protected:
    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    bool IsTagPresentOnOwner(FGameplayTag TagToCheck) const;
};
