#include "Interfaces/PawnUIInterface.h"

UHeroUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
    // Default functionality ifr instances do not override method
    return nullptr;
}

UEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
    // Default functionality if instances do not override method
    return nullptr;
}
