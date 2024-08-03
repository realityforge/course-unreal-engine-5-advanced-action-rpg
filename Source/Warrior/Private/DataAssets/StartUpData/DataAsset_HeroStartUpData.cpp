#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
    return Tag.IsValid() && Ability;
}

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InAbilitySystemComponent,
                                                              const int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InAbilitySystemComponent, ApplyLevel);

    for (const auto& AbilitySet : StartUpAbilitySets)
    {
        if (ensure(AbilitySet.IsValid()))
        {
            FGameplayAbilitySpec AbilitySpec{ AbilitySet.Ability, ApplyLevel };
            AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
            AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.Tag);

            InAbilitySystemComponent->GiveAbility(AbilitySpec);
        }
        else
        {
            // TODO: Report an error
        }
    }
}
