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

    UPROPERTY(VisibleDefaultsOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    float GroundSpeed{ 0.f };

    UPROPERTY(VisibleDefaultsOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    bool bHasAcceleration{ false };

protected:
    FORCEINLINE AWarriorCharacterBase* GetOwningCharacter() const { return OwningCharacter; };
    FORCEINLINE bool HasAcceleration() const { return bHasAcceleration; }

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
