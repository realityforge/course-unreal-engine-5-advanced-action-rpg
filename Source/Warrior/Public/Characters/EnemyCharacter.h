#pragma once

#include "Characters/WarriorCharacterBase.h"
#include "CoreMinimal.h"
#include "EnemyCharacter.generated.h"

class UEnemyCombatComponent;

/**
 * Base class for Enemy characters
 */
UCLASS(Abstract)
class WARRIOR_API AEnemyCharacter : public AWarriorCharacterBase
{
    GENERATED_BODY()

#pragma region Properties

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEnemyCombatComponent> CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEnemyUIComponent> EnemyUIComponent;

#pragma endregion

protected:
    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface.

public:
    AEnemyCharacter();

    //~ Begin PawnCombatInterface Interface.
    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
    //~ End PawnCombatInterface Interface

    //~ Begin IPawnUIInterface Interface.
    virtual UPawnUIComponent* GetPawnUIComponent() const override;
    virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
    //~ End IPawnUIInterface Interface

    FORCEINLINE UEnemyCombatComponent* GetCombatComponent() const { return CombatComponent; }
};
