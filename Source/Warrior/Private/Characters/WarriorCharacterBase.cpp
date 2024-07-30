#include "Characters/WarriorCharacterBase.h"

AWarriorCharacterBase::AWarriorCharacterBase()
{
	// The tick function will never be registered and will never tick.
	PrimaryActorTick.bCanEverTick = false;
	// The tick function will start disabled
	PrimaryActorTick.bStartWithTickEnabled = false;

	// The FX use decals to update the ground, and turning it off for the character
	// mesh means it does not get forced onto character
	GetMesh()->bReceivesDecals = false;
}
