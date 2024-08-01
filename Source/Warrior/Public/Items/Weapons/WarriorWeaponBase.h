#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UBoxComponent;

UCLASS(Abstract, meta = (RuleRangerRequired = "WeaponMesh.StaticMesh"))
class WARRIOR_API AWarriorWeaponBase : public AActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> WeaponMesh{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBoxComponent> WeaponCollisionBox{ nullptr };

public:
    AWarriorWeaponBase();

    FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
