#include "Widgets/WarriorWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (const auto PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
    {
        if (const auto HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
        {
            BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
        }
    }
}

void UWarriorWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
    if (const auto PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
    {
        const auto EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
        checkf(EnemyUIComponent,
               TEXT("UWarriorWidgetBase::InitEnemyCreatedWidget: Failed to extract EnemyUIComponent from %s"),
               *OwningEnemyActor->GetActorNameOrLabel());
        BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
    }
}
