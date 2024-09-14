#include "Components/Combat/HeroCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aeon/Logging.h"
#include "Items/Weapons/WarriorHeroWeapon.h"
#include "WarriorGameplayTags.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroWeaponInInventoryByTag(FGameplayTag InGameplayTag) const
{
    return Cast<AWarriorHeroWeapon>(GetWeaponInInventoryByTag(InGameplayTag));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetEquippedHeroWeapon() const
{
    return Cast<AWarriorHeroWeapon>(GetEquippedWeapon());
}

float UHeroCombatComponent::GetEquippedHeroWeaponDamageAtLevel(const int32 InLevel) const
{
    const auto EquippedHeroWeapon = GetEquippedHeroWeapon();
    return EquippedHeroWeapon ? EquippedHeroWeapon->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel) : 0.f;
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    // Make sure that we can only damage an actor at most once
    if (!GetOverlappedActors().Contains(HitActor))
    {
        GetOverlappedActors().AddUnique(HitActor);

        AEON_SHOW_MESSAGE(FColor::Green,
                          TEXT("%s hit %s"),
                          *GetOwningPawn()->GetActorNameOrLabel(),
                          *HitActor->GetActorNameOrLabel())

        // Send a gameplay event to indicate that damage occurred.
        // It is then the responsibility of a Gameplay Ability
        // to listen for the event.
        // (In our scenario, the Attack ability, initiated an anim montage,
        // that enabled a collision box, that triggered callback on overlap
        // with target, that called combat component)

        FGameplayEventData Data;
        const auto Actor = GetOwningPawn();
        Data.Instigator = Actor;
        Data.Target = HitActor;

        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor,
                                                                 WarriorGameplayTags::Shared_Event_MeleeHit,
                                                                 Data);
    }
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    AEON_SHOW_MESSAGE(FColor::Red,
                      TEXT("%s pulled weapon from %s"),
                      *GetOwningPawn()->GetActorNameOrLabel(),
                      *InteractedActor->GetActorNameOrLabel())
}
