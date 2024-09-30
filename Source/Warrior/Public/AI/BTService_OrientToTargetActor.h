#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "BTService_OrientToTargetActor.generated.h"

/**
 *
 */
UCLASS()
class WARRIOR_API UBTService_OrientToTargetActor final : public UBTService
{
    GENERATED_BODY()

    UBTService_OrientToTargetActor();

    UPROPERTY(EditAnywhere, Category = "Target")
    FBlackboardKeySelector TargetActorKey;

    UPROPERTY(EditAnywhere, Category = "Target")
    float RotationInterpSpeed{ 5.f };

protected:
#pragma region UBTService overrides
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
#pragma endregion

public:
#pragma region UBTNode overrides
    virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
    virtual FString GetStaticDescription() const override;
#pragma endregion
};
