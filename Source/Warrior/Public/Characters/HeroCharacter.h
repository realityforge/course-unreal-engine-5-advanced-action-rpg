#pragma once

#include "Characters/WarriorCharacterBase.h"
#include "CoreMinimal.h"
#include "HeroCharacter.generated.h"

UCLASS()
class WARRIOR_API AHeroCharacter : public AWarriorCharacterBase
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
