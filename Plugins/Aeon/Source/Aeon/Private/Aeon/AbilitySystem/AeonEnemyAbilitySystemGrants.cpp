#include "Aeon/AbilitySystem/AeonEnemyAbilitySystemGrants.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "Aeon/Logging.h"

void UAeonEnemyAbilitySystemGrants::GiveToAbilitySystemComponent(UAeonAbilitySystemComponent* InAbilitySystemComponent,
                                                                 const int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InAbilitySystemComponent, ApplyLevel);

    for (int32 i = 0; i < StartUpAbilities.Num(); i++)
    {
        if (const auto& Ability = StartUpAbilities[i])
        {
            FGameplayAbilitySpec AbilitySpec{ Ability, ApplyLevel };
            AbilitySpec.SourceObject = InAbilitySystemComponent->GetAvatarActor();

            InAbilitySystemComponent->GiveAbility(AbilitySpec);
        }
        else
        {
            AEON_WARNING_ALOG("UAeonEnemyAbilitySystemGrants::GiveToAbilitySystemComponent: "
                              "Invalid Ability specified at index %d of "
                              "StartUpAbilitySets can not be granted. In asset %s",
                              i,
                              *GetName());
        }
    }
}
