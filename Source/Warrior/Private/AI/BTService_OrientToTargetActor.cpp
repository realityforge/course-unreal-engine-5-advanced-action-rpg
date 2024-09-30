#include "AI/BTService_OrientToTargetActor.h"
#include "AIController.h"
#include "Aeon/Logging.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTargetActor::UBTService_OrientToTargetActor()
{
    // This is the Display Name of the node in the BT graph
    NodeName = TEXT("Orient Rotation To Target Actor");

    INIT_SERVICE_NODE_NOTIFY_FLAGS();

    Interval = 0.f;
    RandomDeviation = 0.f;

    TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, TargetActorKey), AActor::StaticClass());
}

void UBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp,
                                              uint8* NodeMemory,
                                              const float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    const auto TargetActor =
        Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

    // ReSharper disable once CppTooWideScopeInitStatement
    const auto OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (OwningPawn && TargetActor)
    {
        const FRotator LookAtRotator =
            UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
        const FRotator NewRotation =
            FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRotator, DeltaSeconds, RotationInterpSpeed);
        OwningPawn->SetActorRotation(NewRotation);
    }
}

void UBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    if (const auto BlackboardAsset = GetBlackboardAsset())
    {
        // Required for TargetActorKey to work properly...
        TargetActorKey.ResolveSelectedKey(*BlackboardAsset);
    }
    else
    {
        AEON_WARNING_ALOG("UBTService_OrientToTargetActor::InitializeFromAsset unable to "
                          "retrieve BlackboardAsset on %s",
                          *GetName());
    }
}

FString UBTService_OrientToTargetActor::GetStaticDescription() const
{
    // This is the string under the Node Display Name
    return FString::Printf(TEXT("Orient rotation to %s Key %s"),
                           *TargetActorKey.SelectedKeyName.ToString(),
                           *GetStaticServiceDescription());
}
