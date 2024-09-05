#pragma once

#include "Aeon/Character/AeonCharacterBase.h"
#include "WarriorCharacterBase.generated.h"

class UWarriorAttributeSet;

UCLASS()
class WARRIOR_API AWarriorCharacterBase : public AAeonCharacterBase
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Warrior|AbilitySystem",
              meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWarriorAttributeSet> WarriorAttributeSet{ nullptr };

public:
    AWarriorCharacterBase();

    virtual void PossessedBy(AController* NewController) override;

    FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
