#include "Characters/EnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
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
}
