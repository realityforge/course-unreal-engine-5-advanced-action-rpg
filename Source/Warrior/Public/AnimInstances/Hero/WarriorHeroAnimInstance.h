#pragma once

#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "CoreMinimal.h"
#include "WarriorHeroAnimInstance.generated.h"

class AHeroCharacter;

UCLASS()
class WARRIOR_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly,
              BlueprintReadOnly,
              Category = "AnimData|References",
              meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AHeroCharacter> OwningHeroCharacter{ nullptr };

    UPROPERTY(VisibleDefaultsOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    bool bShouldEnterRelaxedState{ false };

    /** the max duration in the idle state before we enter relax state. */
    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "AnimData|LocomotionData",
              meta = (AllowPrivateAccess = "true"))
    float EnterRelaxStateThreshold{ 5.f };

    /** The duration since we entered the relaxed state. */
    float IdleElapsedTime{ 0.f };

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
