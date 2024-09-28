#pragma once

#include "AIController.h"
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

public:
    explicit AWarriorAIController(const FObjectInitializer& ObjectInitializer);

#pragma region IGenericTeamAgentInterface Interface
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
#pragma endregion
};
