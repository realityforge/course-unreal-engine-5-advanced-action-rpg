#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*);

UCLASS(Abstract, meta = (RuleRangerRequired = "WeaponMesh.StaticMesh"))
class WARRIOR_API AWarriorWeaponBase : public AActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> WeaponMesh{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBoxComponent> WeaponCollisionBox{ nullptr };

    const APawn* GetPawnInstigator() const;

protected:
    UFUNCTION()
    virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                            AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp,
                                            int32 OtherBodyIndex,
                                            bool bFromSweep,
                                            const FHitResult& SweepResult);
    UFUNCTION()
    virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                          AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp,
                                          int32 OtherBodyIndex);

public:
    AWarriorWeaponBase();

    FOnTargetInteractedDelegate OnWeaponHitTarget;
    FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

    FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
