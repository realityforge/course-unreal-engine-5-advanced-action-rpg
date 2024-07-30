#include "Characters/HeroCharacter.h"

#include "WarriorDebugHelper.h"

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print(TEXT("Welcome"));
}
