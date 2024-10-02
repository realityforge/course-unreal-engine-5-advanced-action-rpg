#pragma once

#include "AnimInstances/WarriorAnimInstanceBase.h"
#include "CoreMinimal.h"
#include "WarriorCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AWarriorCharacterBase;

UCLASS()
class WARRIOR_API UWarriorCharacterAnimInstance : public UWarriorAnimInstanceBase
{
    GENERATED_BODY()

    UPROPERTY()
    TObjectPtr<AWarriorCharacterBase> OwningCharacter{ nullptr };

    UPROPERTY()
    TObjectPtr<UCharacterMovementComponent> OwningMovementComponent{ nullptr };

    UPROPERTY(EditInstanceOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    float GroundSpeed{ 0.f };

    UPROPERTY(EditInstanceOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    bool bHasAcceleration{ false };

    /** Is the character strafing? */
    UPROPERTY(EditInstanceOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    bool bStrafing{ false };

    /** Direction of character in degrees. Ranging from -180 to 180. */
    UPROPERTY(EditInstanceOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    float LocomotionDirection{ 0.f };

protected:
    FORCEINLINE AWarriorCharacterBase* GetOwningCharacter() const { return OwningCharacter; };
    FORCEINLINE bool HasAcceleration() const { return bHasAcceleration; }

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
