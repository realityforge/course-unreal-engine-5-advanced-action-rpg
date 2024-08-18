#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "Aeon/AbilitySystem/AeonGameplayAbilitySet.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                              const int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InAbilitySystemComponent, ApplyLevel);

    for (const auto& AbilitySet : StartUpAbilitySets)
    {
        if (ensure(AbilitySet.IsValid()))
        {
            FGameplayAbilitySpec AbilitySpec{ AbilitySet.Ability, ApplyLevel };
            AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
            AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

            InAbilitySystemComponent->GiveAbility(AbilitySpec);
        }
        else
        {
            // TODO: Report an error
        }
    }
}
