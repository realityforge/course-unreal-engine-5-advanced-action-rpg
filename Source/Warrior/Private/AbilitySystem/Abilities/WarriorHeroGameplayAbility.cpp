#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/HeroCharacter.h"
#include "Controllers/HeroPlayerController.h"

AHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!HeroCharacterCache.IsValid())
    {
        HeroCharacterCache = CastChecked<AHeroCharacter>(GetAvatarActorFromActorInfo());
    }
    return HeroCharacterCache.Get();
}

AWarriorHeroPlayerController* UWarriorHeroGameplayAbility::GetWarriorHeroPlayerController()
{
    if (!WarriorHeroPlayerControllerCache.IsValid())
    {
        WarriorHeroPlayerControllerCache = CastChecked<AWarriorHeroPlayerController>(GetActorInfo().PlayerController);
    }
    return WarriorHeroPlayerControllerCache.Get();
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetCombatComponent();
}
