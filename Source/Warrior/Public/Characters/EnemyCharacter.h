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

    FORCEINLINE UEnemyCombatComponent* GetCombatComponent() const { return CombatComponent; }
};
