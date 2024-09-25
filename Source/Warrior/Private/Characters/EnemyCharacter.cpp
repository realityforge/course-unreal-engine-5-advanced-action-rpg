#include "Characters/EnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

    CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("CombatComponent");
    EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    GiveStartUpDataToAbilitySystemAsync();
}

UPawnCombatComponent* AEnemyCharacter::GetPawnCombatComponent() const
{
    return CombatComponent;
}

UPawnUIComponent* AEnemyCharacter::GetPawnUIComponent() const
{
    return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
    return EnemyUIComponent;
}
