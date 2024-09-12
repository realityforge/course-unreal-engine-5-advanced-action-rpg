#include "Items/Weapons/WarriorWeaponBase.h"
#include "Aeon/Logging.h"
#include "Components/BoxComponent.h"

AWarriorWeaponBase::AWarriorWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(WeaponMesh);

    WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
    WeaponCollisionBox->SetupAttachment(WeaponMesh);
    WeaponCollisionBox->SetBoxExtent(FVector(20.f));
    WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWarriorWeaponBase::OnCollisionBoxBeginOverlap);
    WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AWarriorWeaponBase::OnCollisionBoxEndOverlap);
}

const APawn* AWarriorWeaponBase::GetPawnInstigator() const
{
    const auto PawnInstigator = GetInstigator<APawn>();
    checkf(PawnInstigator,
           TEXT("AWarriorWeaponBase::GetPawnInstigator invoked. "
                "No instigator assigned as owner of the Weapon %s. Please fix."),
           *GetName());
    return PawnInstigator;
}

void AWarriorWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                    AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp,
                                                    int32 OtherBodyIndex,
                                                    bool bFromSweep,
                                                    const FHitResult& SweepResult)
{
    const auto PawnInstigator = GetPawnInstigator();
    if (const auto HitPawn = Cast<APawn>(OtherActor))
    {
        // You should not be able to hit yourself
        if (PawnInstigator != HitPawn)
        {
            OnWeaponHitTarget.ExecuteIfBound(OtherActor);
        }
    }
}

void AWarriorWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                  AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp,
                                                  int32 OtherBodyIndex)
{
    const auto PawnInstigator = GetPawnInstigator();
    if (const auto HitPawn = Cast<APawn>(OtherActor))
    {
        // You should not be able to hit yourself
        if (PawnInstigator != HitPawn)
        {
            OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
        }
    }
}
