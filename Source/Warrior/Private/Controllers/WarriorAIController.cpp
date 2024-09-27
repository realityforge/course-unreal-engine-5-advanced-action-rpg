#include "Controllers/WarriorAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer
                // Override PathFollowingComponent to implement Detour Crowd Avoidance
                .SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    check(Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()));
}
