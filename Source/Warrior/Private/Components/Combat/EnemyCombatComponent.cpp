#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aeon/Logging.h"
#include "WarriorGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (!GetOverlappedActors().Contains(HitActor))
    {
        GetOverlappedActors().AddUnique(HitActor);

        // TODO: Implement block check
        bool bIsValidBlock = false;

        const bool bIsPlayerBlocking = false;
        const bool bIsAttackUnblockable = false;

        if (bIsPlayerBlocking && !bIsAttackUnblockable)
        {
            // TODO: check if block is valid
        }

        FGameplayEventData EventData;
        EventData.Instigator = GetOwningPawn();
        EventData.Target = HitActor;

        if (bIsValidBlock)
        {
            /// TODO: Handle Successfule Block
        }
        else
        {
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
                                                                     WarriorGameplayTags::Shared_Event_MeleeHit,
                                                                     EventData);
        }
    }
}
