#include "AI/BTTask_RotateToFaceTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
    NodeName = TEXT("Rotate To Face Target Actor");

    bNotifyTick = true;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = true;

    INIT_TASK_NODE_NOTIFY_FLAGS();
    TargetToFace.AddObjectFilter(this,
                                 GET_MEMBER_NAME_CHECKED(UBTTask_RotateToFaceTarget, TargetToFace),
                                 AActor::StaticClass());
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
    return sizeof(FRotateToFaceTargetTaskMemory);
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    if (const auto BlackboardAsset = GetBlackboardAsset())
    {
        // Make sure we resolve the key
        TargetToFace.ResolveSelectedKey(*BlackboardAsset);
    }
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
    return FString::Printf(TEXT("Rotates to face %s key until the "
                                "angle prevision %s is reached"),
                           *TargetToFace.SelectedKeyName.ToString(),
                           *FString::SanitizeFloat(AnglePrecision));
}

bool UBTTask_RotateToFaceTarget::HasReachedAnglePrecision(const APawn* OwnerPawn, const AActor* TargetActor) const
{
    const auto OwnerToTargetNormalized =
        (TargetActor->GetActorLocation() - OwnerPawn->GetActorLocation()).GetSafeNormal();
    const float DotResult = FVector::DotProduct(OwnerPawn->GetActorForwardVector(), OwnerToTargetNormalized);
    return UKismetMathLibrary::DegAcos(DotResult) <= AnglePrecision;
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
    check(Memory);

    const auto TargetActor =
        Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetToFace.SelectedKeyName));
    const auto OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
    Memory->OwningPawn = OwningPawn;
    Memory->TargetActor = TargetActor;
    if (!Memory->IsValid())
    {
        // No target actor
        return EBTNodeResult::Failed;
    }
    else if (HasReachedAnglePrecision(OwningPawn, TargetActor))
    {
        Memory->Reset();
        return EBTNodeResult::Succeeded;
    }
    else
    {
        return EBTNodeResult::InProgress;
    }
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp,
                                          uint8* NodeMemory,
                                          const float DeltaSeconds)
{
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
    if (!Memory->IsValid())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
    else if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
    {
        Memory->Reset();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        // Interpolate between current rotation and target rotation
        const FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(),
                                                                              Memory->TargetActor->GetActorLocation());
        const FRotator TargetRot =
            FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(), LookAtRotator, DeltaSeconds, RotationInterpSpeed);
        Memory->OwningPawn->SetActorRotation(TargetRot);
    }
}
