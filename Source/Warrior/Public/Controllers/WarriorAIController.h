#pragma once

#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKey.h"
#include "CoreMinimal.h"
#include "WarriorAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

/**
 * Base class for AI controllers in the warrior project.
 */
UCLASS(Abstract)
class WARRIOR_API AWarriorAIController : public AAIController
{
    GENERATED_BODY()

    /** Behavior tree to use on possession. */
    UPROPERTY(EditAnywhere,
              Category = "Warrior",
              BlueprintReadOnly,
              meta = (AllowPrivateAccess = "true", RuleRangerRequired = "true"))
    TObjectPtr<UBehaviorTree> BehaviorTree;

#pragma region BlackBoard Keys
    // Cached Blackboard Keys. Populated during possession to minimize
    // runtime cost when using keys and centralize error handling
    FBlackboard::FKey TargetActorKeyID;
#pragma endregion

protected:
#pragma region Components

    /** Component used to register as stimuli listener in AIPerceptionSystem. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;
#pragma endregion

    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    /**
     * Lookup and cache Blackboard KeyID with specified name in OutKeyID.
     * An ensure check will be tripped if the key is not found.
     *
     * @param KeyName the name of the key
     * @param OutKeyID the place to store the cached key
     */
    void LookupBlackboardKey(const FName KeyName, FBlackboard::FKey& OutKeyID);

    virtual void OnPossess(APawn* InPawn) override;

public:
    explicit AWarriorAIController(const FObjectInitializer& ObjectInitializer);

#pragma region IGenericTeamAgentInterface Interface
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
#pragma endregion
};
