#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/HeroCharacter.h"
#include "Controllers/HeroPlayerController.h"

AHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!HeroCharacterCache.IsValid() && IsValid(GetAvatarActorFromActorInfo()))
    {
        HeroCharacterCache = CastChecked<AHeroCharacter>(GetAvatarActorFromActorInfo());
    }
    return HeroCharacterCache.IsValid() ? HeroCharacterCache.Get() : nullptr;
}

AWarriorHeroPlayerController* UWarriorHeroGameplayAbility::GetWarriorHeroPlayerController()
{
    if (!WarriorHeroPlayerControllerCache.IsValid() && GetActorInfo().PlayerController.IsValid(false))
    {
        WarriorHeroPlayerControllerCache = CastChecked<AWarriorHeroPlayerController>(GetActorInfo().PlayerController);
    }
    return WarriorHeroPlayerControllerCache.IsValid() ? WarriorHeroPlayerControllerCache.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetCombatComponent();
}
