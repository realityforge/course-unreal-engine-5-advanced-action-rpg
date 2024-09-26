#pragma once

#include "Characters/WarriorCharacterBase.h"
#include "CoreMinimal.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;

#pragma endregion

protected:
    //~ Begin AActor Interface.
    virtual void BeginPlay() override;
    //~ End APawn Interface.

    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface.

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR

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
