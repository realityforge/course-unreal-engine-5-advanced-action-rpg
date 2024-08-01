#include "Items/Weapons/WarriorWeaponBase.h"
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
}
