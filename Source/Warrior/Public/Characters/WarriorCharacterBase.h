#pragma once

#include "Aeon/Character/AeonCharacterBase.h"
#include "Interfaces/PawnCombatInterface.h"
#include "WarriorCharacterBase.generated.h"

class UWarriorAttributeSet;

UCLASS()
class WARRIOR_API AWarriorCharacterBase : public AAeonCharacterBase, public IPawnCombatInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Warrior|AbilitySystem",
              meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWarriorAttributeSet> WarriorAttributeSet{ nullptr };

public:
    AWarriorCharacterBase();

    //~ Begin IPawnCombatInterface Interface.
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
    //~ End IPawnCombatInterface Interface

    virtual void PossessedBy(AController* NewController) override;

    FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
