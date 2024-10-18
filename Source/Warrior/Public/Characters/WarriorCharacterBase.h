#pragma once

#include "Aeon/Character/AeonCharacterBase.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "WarriorCharacterBase.generated.h"

class UWarriorAttributeSet;
class UMotionWarpingComponent;

UCLASS()
class WARRIOR_API AWarriorCharacterBase :
    public AAeonCharacterBase,
    public IPawnCombatInterface,
    public IPawnUIInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Warrior|AbilitySystem",
              meta = (AllowPrivateAccess = "true"))
    TObjectPtr<const UWarriorAttributeSet> WarriorAttributeSet{ nullptr };

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Warrior|MotionWarping",
              meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent{ nullptr };

public:
    AWarriorCharacterBase();

    //~ Begin IPawnCombatInterface Interface.
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
    //~ End IPawnCombatInterface Interface

    //~ Begin IPawnUIInterface Interface.
    virtual UPawnUIComponent* GetPawnUIComponent() const override;
    //~ End IPawnUIInterface Interface

    virtual void PossessedBy(AController* NewController) override;

    FORCEINLINE const UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
