#include "Interfaces/PawnUIInterface.h"

UHeroUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
    // Default functionality ifr instances do not override method
    return nullptr;
}
