#include "Components/Combat/HeroCombatComponent.h"
#include "Aeon/Logging.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroWeaponInInventoryByTag(FGameplayTag InGameplayTag) const
{
    return Cast<AWarriorHeroWeapon>(GetWeaponInInventoryByTag(InGameplayTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    AEON_SHOW_MESSAGE(FColor::Green,
                      TEXT("%s hit %s"),
                      *GetOwningPawn()->GetActorNameOrLabel(),
                      *HitActor->GetActorNameOrLabel())
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    AEON_SHOW_MESSAGE(FColor::Red,
                      TEXT("%s pulled weapon from %s"),
                      *GetOwningPawn()->GetActorNameOrLabel(),
                      *InteractedActor->GetActorNameOrLabel())
}
