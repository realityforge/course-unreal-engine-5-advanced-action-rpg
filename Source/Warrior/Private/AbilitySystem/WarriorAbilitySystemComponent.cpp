#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Aeon/Logging.h"
#include "WarriorTypes/WarriorStructTypes.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InTag)
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

            AEON_WARNING_ALOG("UWarriorAbilitySystemComponent::OnAbilityInputPressed: "
                              "Unable to activate any ability with tag %s",
                              *InTag.ToString());
        }
    }
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InTag) {}

void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(
    const TArray<FWarriorHeroAbilitySet>& InAbilities,
    const int32 InApplyLevel,
    TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
    if (!InAbilities.IsEmpty())
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
                    AEON_ERROR_ALOG("UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities: "
                                    "Failed to grant ability (Tag %s, Ability %s) to %s",
                                    *AbilitySet.InputTag.ToString(),
                                    AbilitySet.Ability ? *AbilitySet.Ability->GetFullName() : TEXT(""),
                                    *GetName());
                }
            }
            else
            {
                AEON_ERROR_ALOG("UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities: "
                                "Invalid AbilitySet unable to be granted. Tag %s, Ability %s",
                                *AbilitySet.InputTag.ToString(),
                                AbilitySet.Ability ? *AbilitySet.Ability->GetFullName() : TEXT(""));
            }
        }
    }
}

void UWarriorAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
    const TArray<FGameplayAbilitySpecHandle>& InAbilitySpecHandles)
{
    if (!InAbilitySpecHandles.IsEmpty())
    {
        for (const auto& SpecHandle : InAbilitySpecHandles)
        {
            ClearAbility(SpecHandle);
        }
    }
}
