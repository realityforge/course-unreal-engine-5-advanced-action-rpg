#include "Aeon/Character/AeonCharacterBase.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "Aeon/AbilitySystem/AeonAttributeSet.h"
#include "Aeon/Logging.h"

AAeonCharacterBase::AAeonCharacterBase()
{
    // The tick function will never be registered and will never tick.
    PrimaryActorTick.bCanEverTick = false;
    // The tick function will start disabled
    PrimaryActorTick.bStartWithTickEnabled = false;

    AeonAbilitySystemComponent =
        CreateDefaultSubobject<UAeonAbilitySystemComponent>(TEXT("AeonAbilitySystemComponent"));

    AeonAttributeSet = CreateDefaultSubobject<UAeonAttributeSet>(TEXT("AeonAttributeSet"));
}

UAbilitySystemComponent* AAeonCharacterBase::GetAbilitySystemComponent() const
{
    return GetAeonAbilitySystemComponent();
}

void AAeonCharacterBase::GiveStartUpDataToAbilitySystem() const
{
    if (ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("CharacterStartUpData has not been assigned")))
    {
        if (const auto Data = CharacterStartUpData.LoadSynchronous())
        {
            Data->GiveToAbilitySystemComponent(AeonAbilitySystemComponent);
        }
        else
        {
            ensureMsgf(false, TEXT("CharacterStartUpData %s failed to load"), *CharacterStartUpData.GetAssetName());
        }
    }
}

void AAeonCharacterBase::InitAbilityActorInfo()
{
    if (ensureMsgf(GetAeonAbilitySystemComponent(), TEXT("AeonAbilitySystemComponent not configured for Character")))
    {
        GetAeonAbilitySystemComponent()->InitAbilityActorInfo(this, this);

        ensureMsgf(!CharacterStartUpData.IsNull(),
                   TEXT("AAeonCharacterBase::InitAbilityActorInfo: CharacterStartUpData not assigned to %s"),
                   *GetName());
    }
    else
    {
        AEON_ERROR_ALOG("AeonAbilitySystemComponent not configured for Character");
    }
}
