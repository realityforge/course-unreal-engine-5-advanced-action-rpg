#include "Controllers/WarriorAIController.h"
#include "Aeon/Logging.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer
                // Override PathFollowingComponent to implement Detour Crowd Avoidance
                .SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    check(Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()));

    AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

    // Enemies can only detect other enemies (i.e. the player)
    AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
    AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
    AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

    // Maximum sight distance to notice a target.
    AISenseConfig_Sight->SightRadius = 5000.f;
    // Disable the ability for the ai to lose track of target if they just get too far away by setting to 0
    AISenseConfig_Sight->LoseSightRadius = 0.f;

    // Enemy can see 360 degrees ... not line of sight as such
    AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
    AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this,
                                                                      &AWarriorAIController::OnTargetPerceptionUpdated);

    // Make sure we explicitly set common team for all AI so that they are on a single team
    AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AWarriorAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
        if (GetBlackboardComponent())
        {
            LookupBlackboardKey(FName("TargetActor"), TargetActorKeyID);
        }
        else
        {
            AEON_WARNING_ALOG("AWarriorAIController::OnPossess: Failed to retrieve "
                              "BlackboardComponent and thus no blackboard keys cached")
        }
    }
    else
    {
        AEON_WARNING_ALOG("AWarriorAIController::OnPossess: BehaviorTree not configured")
    }
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const APawn* OtherPawn = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface* OtherTeamAgent =
        Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());

    // Enemy AI will consider every team other than their own to be the enemy
    return OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId() ? ETeamAttitude::Hostile
                                                                                      : ETeamAttitude::Friendly;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppPassValueParameterByConstReference
void AWarriorAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Stimulus.WasSuccessfullySensed() && Actor)
    {
    }
}
