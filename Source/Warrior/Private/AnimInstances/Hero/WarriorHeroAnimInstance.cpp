#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"
#include "Characters/HeroCharacter.h"
#include "Characters/WarriorCharacterBase.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (GetOwningCharacter())
    {
        OwningHeroCharacter = Cast<AHeroCharacter>(GetOwningCharacter());
    }
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(const float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    if (HasAcceleration())
    {
        IdleElapsedTime = 0.f;
        bShouldEnterRelaxedState = false;
    }
    else
    {
        IdleElapsedTime += DeltaSeconds;
        bShouldEnterRelaxedState = IdleElapsedTime >= EnterRelaxStateThreshold;
    }
}
