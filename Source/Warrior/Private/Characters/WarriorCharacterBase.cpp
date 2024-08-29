#include "Characters/WarriorCharacterBase.h"

AWarriorCharacterBase::AWarriorCharacterBase()
{
    // The FX use decals to update the ground, and turning it off for the
    // character mesh means it does not get forced onto character
    GetMesh()->bReceivesDecals = false;
}

void AWarriorCharacterBase::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitAbilityActorInfo();
}
