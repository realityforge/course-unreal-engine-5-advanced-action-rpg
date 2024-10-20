#include "Characters/WarriorCharacterBase.h"
#include "AbilitySystem/Attributes/WarriorAttributeSet.h"
#include "MotionWarpingComponent.h"

AWarriorCharacterBase::AWarriorCharacterBase()
{
    // The FX use decals to update the ground, and turning it off for the
    // character mesh means it does not get forced onto character
    GetMesh()->bReceivesDecals = false;

    WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));

    // Component used to warp enemy character towards player when attacking
    MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

void AWarriorCharacterBase::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitAbilityActorInfo();
}

UPawnCombatComponent* AWarriorCharacterBase::GetPawnCombatComponent() const
{
    checkf(false,
           TEXT("AWarriorCharacterBase::GetPawnCombatComponent invoked when it is expected to have been overridden"));
    return nullptr;
}

UPawnUIComponent* AWarriorCharacterBase::GetPawnUIComponent() const
{
    checkf(false,
           TEXT("AWarriorCharacterBase::GetPawnUIComponent invoked when it is expected to have been overridden"));
    return nullptr;
}
