#include "Controllers/WarriorAIController.h"
#include "Aeon/Logging.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
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

void AWarriorAIController::LookupBlackboardKey(const FName KeyName, FBlackboard::FKey& OutKeyID)
{
    const auto BlackboardComponent = GetBlackboardComponent();
    checkf(BlackboardComponent, TEXT("Expected BlackboardComponent to be present"));
    const FBlackboard::FKey KeyID = BlackboardComponent->GetKeyID(KeyName);
    ensureAlwaysMsgf(FBlackboard::InvalidKey != KeyID,
                     TEXT("Failed to retrieve '%s' key from "
                          "Blackboard named '%s' defined on Controller named '%s' "
                          "with Behavior Tree named '%s'"),
                     *KeyName.ToString(),
                     BlackboardComponent->GetBlackboardAsset() ? *BlackboardComponent->GetBlackboardAsset()->GetName()
                                                               : TEXT("(None)"),
                     *GetName(),
                     *BehaviorTree->GetName());
    OutKeyID = KeyID;
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

void AWarriorAIController::BeginPlay()
{
    Super::BeginPlay();
    auto CrowdFollowingComponent = CastChecked<UCrowdFollowingComponent>(GetPathFollowingComponent());
    CrowdFollowingComponent->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled
                                                                                 : ECrowdSimulationState::Disabled);
    switch (DetourCrowdAvoidanceQuality)
    {
        case 1:
            CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
            break;
        case 2:
            CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
            break;
        case 3:
            CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
        case 4:
            CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
            break;
        default:
            AEON_WARNING_ALOG(
                " AWarriorAIController::DetourCrowdAvoidanceQuality set to bad value. Expected to be 1-4 but is %d",
                DetourCrowdAvoidanceQuality);
    }
    CrowdFollowingComponent->SetAvoidanceGroup(1);
    CrowdFollowingComponent->SetGroupsToAvoid(1);
    CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const APawn* OtherPawn = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface* OtherTeamAgent =
        Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());

    // Enemy AI will consider every team other than their own to be the enemy
    return OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId() ? ETeamAttitude::Hostile
                                                                                     : ETeamAttitude::Friendly;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppPassValueParameterByConstReference
void AWarriorAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (const auto BlackboardComponent = GetBlackboardComponent())
    {
        if (!BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TargetActorKeyID))
        {
            if (Stimulus.WasSuccessfullySensed() && Actor)
            {
                BlackboardComponent->SetValue<UBlackboardKeyType_Object>(TargetActorKeyID, Actor);
            }
        }
    }
    else
    {
        AEON_SHOW_INFO_MESSAGE(TEXT("AWarriorAIController::OnTargetPerceptionUpdated BlackboardComponent invalid"));
    }
}
