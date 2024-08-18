#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "Aeon/AbilitySystem/AeonGameplayAbilitySet.h"
#include "Aeon/Logging.h"

void UAeonAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InTag)
{
    if (ensure(InTag.IsValid()))
    {
        bool bActivationOccurred = false;
        for (const auto AbilitySpec : GetActivatableAbilities())
        {
            if (AbilitySpec.DynamicAbilityTags.HasTagExact(InTag))
            {
                TryActivateAbility(AbilitySpec.Handle);
                bActivationOccurred = true;
            }
        }
        if (!bActivationOccurred)
        {

            AEON_WARNING_ALOG("UAeonAbilitySystemComponent::OnAbilityInputPressed: "
                              "Unable to activate any ability with tag %s",
                              *InTag.ToString());
        }
    }
    else
    {
        AEON_WARNING_ALOG("UAeonAbilitySystemComponent::OnAbilityInputPressed: Invalid tag parameter");
    }
}

void UAeonAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InTag) {}

void UAeonAbilitySystemComponent::GrantHeroWeaponAbilities(
    const TArray<FAeonGameplayAbilitySet>& InAbilities,
    const int32 InApplyLevel,
    TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
    for (const auto& AbilitySet : InAbilities)
    {
        if (AbilitySet.IsValid())
        {
            FGameplayAbilitySpec AbilitySpec(AbilitySet.Ability, InApplyLevel);
            AbilitySpec.SourceObject = GetAvatarActor();
            AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

            if (FGameplayAbilitySpecHandle Handle = GiveAbility(AbilitySpec); Handle.IsValid())
            {
                OutGrantedAbilitySpecHandles.AddUnique(Handle);
            }
            else
            {
                AEON_ERROR_ALOG("UAeonAbilitySystemComponent::GrantHeroWeaponAbilities: "
                                "Failed to grant ability (Tag %s, Ability %s) to %s",
                                *AbilitySet.InputTag.ToString(),
                                AbilitySet.Ability ? *AbilitySet.Ability->GetFullName() : TEXT(""),
                                *GetName());
            }
        }
        else
        {
            AEON_ERROR_ALOG("UAeonAbilitySystemComponent::GrantHeroWeaponAbilities: "
                            "Invalid AbilitySet unable to be granted. Tag %s, Ability %s",
                            *AbilitySet.InputTag.ToString(),
                            AbilitySet.Ability ? *AbilitySet.Ability->GetFullName() : TEXT(""));
        }
    }
}

void UAeonAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
    const TArray<FGameplayAbilitySpecHandle>& InAbilitySpecHandles)
{
    for (const auto& SpecHandle : InAbilitySpecHandles)
    {
        ClearAbility(SpecHandle);
    }
}
