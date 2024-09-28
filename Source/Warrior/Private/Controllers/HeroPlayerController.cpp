#include "Controllers/HeroPlayerController.h"

AWarriorHeroPlayerController::AWarriorHeroPlayerController()
{
    HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AWarriorHeroPlayerController::GetGenericTeamId() const
{
    return HeroTeamID;
}
