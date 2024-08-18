#include "Aeon/AbilitySystem/AeonHeroAbilitySystemGrants.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "Aeon/AbilitySystem/AeonGameplayAbilitySet.h"
#include "Aeon/Logging.h"

void UAeonHeroAbilitySystemGrants::GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                                const int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InAbilitySystemComponent, ApplyLevel);

    for (int32 i = 0; i < StartUpAbilitySets.Num(); i++)
    {
        // ReSharper disable once CppTooWideScopeInitStatement
        const auto& AbilitySet = StartUpAbilitySets[i];
        if (AbilitySet.IsValid())
        {
            FGameplayAbilitySpec AbilitySpec{ AbilitySet.Ability, ApplyLevel };
            AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
            AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

            InAbilitySystemComponent->GiveAbility(AbilitySpec);
        }
        else
        {
            AEON_WARNING_ALOG("UAeonHeroAbilitySystemGrants::GiveToAbilitySystemComponent: "
                              "Invalid AbilitySet specified at index %d of "
                              "StartUpAbilitySets can not be granted. IN asset %s",
                              i,
                              *GetName());
        }
    }
}
