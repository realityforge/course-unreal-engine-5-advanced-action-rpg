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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEnemyCombatComponent> CombatComponent;

public:
    AEnemyCharacter();

    FORCEINLINE UEnemyCombatComponent* GetCombatComponent() const { return CombatComponent; }
};
