#include "Aeon/Character/AeonCharacterBase.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemGrantsBase.h"
#include "Aeon/Logging.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

AAeonCharacterBase::AAeonCharacterBase()
{
    // The tick function will never be registered and will never tick.
    PrimaryActorTick.bCanEverTick = false;
    // The tick function will start disabled
    PrimaryActorTick.bStartWithTickEnabled = false;

    AeonAbilitySystemComponent =
        CreateDefaultSubobject<UAeonAbilitySystemComponent>(TEXT("AeonAbilitySystemComponent"));
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
            constexpr int32 ApplyLevel = 1;
            Data->GiveToAbilitySystemComponent(AeonAbilitySystemComponent, ApplyLevel);
        }
        else
        {
            ensureMsgf(false, TEXT("CharacterStartUpData %s failed to load"), *CharacterStartUpData.GetAssetName());
        }
    }
}

void AAeonCharacterBase::GiveStartUpDataToAbilitySystemAsync() const
{
    if (ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("CharacterStartUpData has not been assigned")))
    {
        constexpr int32 ApplyLevel = 1;
        auto& StreamableManager = UAssetManager::GetStreamableManager();
        const auto Result = StreamableManager.RequestAsyncLoad(
            CharacterStartUpData.ToSoftObjectPath(),
            FStreamableDelegate::CreateLambda([this, ApplyLevel]() {
                if (const auto Data = CharacterStartUpData.Get())
                {
                    Data->GiveToAbilitySystemComponent(AeonAbilitySystemComponent, ApplyLevel);
                    AEON_INFO_ALOG("Loaded CharacterStartUpData %s and granted to AbilitySystemComponent for Actor %s",
                                   *CharacterStartUpData.GetAssetName(),
                                   *GetName());
                }
                else
                {
                    ensureMsgf(false,
                               TEXT("CharacterStartUpData %s failed to load async"),
                               *CharacterStartUpData.GetAssetName());
                }
            }));
        ensureMsgf(Result.IsValid(),
                   TEXT("RequestAsyncLoad for CharacterStartUpData %s failed"),
                   *CharacterStartUpData.GetAssetName());
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
