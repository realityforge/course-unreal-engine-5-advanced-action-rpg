#pragma once

#include "WarriorStructTypes.generated.h"

class UWarriorHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
    GENERATED_BODY()

    /** The AnimLayer that we need to link when this weapon is equipped */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayer;
};
