#pragma once

#include "Aeon/Character/AeonCharacterBase.h"
#include "CoreMinimal.h"
#include "WarriorCharacterBase.generated.h"

UCLASS()
class WARRIOR_API AWarriorCharacterBase : public AAeonCharacterBase
{
    GENERATED_BODY()

public:
    AWarriorCharacterBase();

    virtual void PossessedBy(AController* NewController) override;
};
