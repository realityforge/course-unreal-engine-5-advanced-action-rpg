#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "Characters/WarriorCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
    OwningCharacter = Cast<AWarriorCharacterBase>(TryGetPawnOwner());
    if (OwningCharacter)
    {
        // OwningCharacter can be null because the AnimInstance is also instantiated in the Editor which does not have
        // an associated Owner
        OwningMovementComponent = OwningCharacter->GetCharacterMovement();
    }
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    if (OwningCharacter && OwningMovementComponent)
    {
        GroundSpeed = OwningCharacter->GetVelocity().Size2D();
        bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().Size2D() > 0.f;

        LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(),
                                                                          OwningCharacter->GetActorRotation());
        bStrafing =
            UWarriorFunctionLibrary::NativeIsGameplayTagPresentOnActor(OwningCharacter,
                                                                       WarriorGameplayTags::Enemy_Status_Strafing);
    }
}
