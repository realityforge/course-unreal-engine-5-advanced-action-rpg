#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "BTTask_RotateToFaceTarget.generated.h"

struct FRotateToFaceTargetTaskMemory
{
    TWeakObjectPtr<APawn> OwningPawn{ nullptr };
    TWeakObjectPtr<AActor> TargetActor{ nullptr };

    bool IsValid() const { return OwningPawn.IsValid() && TargetActor.IsValid(); }

    void Reset()
    {
        OwningPawn.Reset();
        TargetActor.Reset();
    }
};

UCLASS()
class WARRIOR_API UBTTask_RotateToFaceTarget : public UBTTaskNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Face Target", meta = (AllowPrivateAccess = "true"))
    float AnglePrecision{ 10.f };

    UPROPERTY(EditAnywhere, Category = "Face Target", meta = (AllowPrivateAccess = "true"))
    float RotationInterpSpeed{ 5.f };

    UPROPERTY(EditAnywhere, Category = "Face Target", meta = (AllowPrivateAccess = "true"))
    FBlackboardKeySelector TargetToFace;

    bool HasReachedAnglePrecision(const APawn* OwnerPawn, const AActor* TargetActor) const;

public:
    UBTTask_RotateToFaceTarget();

#pragma region UBTTaskNode Interface
    virtual uint16 GetInstanceMemorySize() const override;
    virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
    virtual FString GetStaticDescription() const override;
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
#pragma endregion
};
