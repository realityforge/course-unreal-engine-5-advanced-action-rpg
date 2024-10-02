#include "Components/Combat/EnemyCombatComponent.h"
#include "Aeon/Logging.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (HitActor)
    {
        AEON_SHOW_INFO_MESSAGE(TEXT("%s Hit %s"),
                               *GetOwningPawn()->GetActorNameOrLabel(),
                               *HitActor->GetActorNameOrLabel());
    }
}
