#include "Characters/WarriorCharacterBase.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/WarriorAttributeSet.h"
#include "Aeon/Logging.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

AWarriorCharacterBase::AWarriorCharacterBase()
{
    // The tick function will never be registered and will never tick.
    PrimaryActorTick.bCanEverTick = false;
    // The tick function will start disabled
    PrimaryActorTick.bStartWithTickEnabled = false;

    // The FX use decals to update the ground, and turning it off for the
    // character mesh means it does not get forced onto character
    GetMesh()->bReceivesDecals = false;

    WarriorAbilitySystemComponent =
        CreateDefaultSubobject<UWarriorAbilitySystemComponent>(TEXT("WarriorAbilitySystemComponent"));
    WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));
}

void AWarriorCharacterBase::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (ensure(WarriorAbilitySystemComponent))
    {
        WarriorAbilitySystemComponent->InitAbilityActorInfo(this, this);

        ensureMsgf(!CharacterStartUpData.IsNull(),
                   TEXT("AWarriorCharacterBase::PossessedBy: CharacterStartUpData not assigned to %s"),
                   *GetName());
    }
    else
    {
        AEON_ERROR_ALOG("WarriorAbilitySystemComponent not configured for Character");
    }
}

UAbilitySystemComponent* AWarriorCharacterBase::GetAbilitySystemComponent() const
{
    return GetWarriorAbilitySystemComponent();
}

void AWarriorCharacterBase::GiveStartUpDataToAbilitySystem() const
{
    if (ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("CharacterStartUpData has not been assigned")))
    {
        if (const auto Data = CharacterStartUpData.LoadSynchronous())
        {
            Data->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
        }
        else
        {
            ensureMsgf(false, TEXT("CharacterStartUpData %s failed to load"), *CharacterStartUpData.GetAssetName());
        }
    }
}
