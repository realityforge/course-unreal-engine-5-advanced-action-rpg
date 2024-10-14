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
    if (ensureMsgf(!CharacterStartUpData.IsNull(),
                   TEXT("CharacterStartUpData has not been assigned to actor %s"),
                   *GetActorNameOrLabel()))
    {
        if (const auto Data = CharacterStartUpData.LoadSynchronous())
        {
            constexpr int32 ApplyLevel = 1;
            Data->GiveToAbilitySystemComponent(AeonAbilitySystemComponent, ApplyLevel);
        }
        else
        {
            ensureMsgf(false,
                       TEXT("CharacterStartUpData %s failed to load for actor %s"),
                       *CharacterStartUpData.GetAssetName(),
                       *GetActorNameOrLabel());
        }
    }
}

void AAeonCharacterBase::GiveStartUpDataToAbilitySystemAsync() const
{
    if (ensureMsgf(!CharacterStartUpData.IsNull(),
                   TEXT("CharacterStartUpData has not been assigned for actor %s"),
                   *GetActorNameOrLabel()))
    {
        constexpr int32 ApplyLevel = 1;
        auto& StreamableManager = UAssetManager::GetStreamableManager();
        const auto Result = StreamableManager.RequestAsyncLoad(
            CharacterStartUpData.ToSoftObjectPath(),
            FStreamableDelegate::CreateLambda([this, ApplyLevel]() {
                if (const auto Data = CharacterStartUpData.Get())
                {
                    Data->GiveToAbilitySystemComponent(AeonAbilitySystemComponent, ApplyLevel);
                    AEON_INFO_ALOG("Loaded CharacterStartUpData %s and granted to AbilitySystemComponent for actor %s",
                                   *CharacterStartUpData.GetAssetName(),
                                   *GetActorNameOrLabel());
                }
                else
                {
                    ensureMsgf(false,
                               TEXT("CharacterStartUpData %s failed to load async for actor %s"),
                               *CharacterStartUpData.GetAssetName(),
                               *GetActorNameOrLabel());
                }
            }));
        ensureMsgf(Result.IsValid(),
                   TEXT("RequestAsyncLoad for CharacterStartUpData %s failed for actor %s"),
                   *CharacterStartUpData.GetAssetName(),
                   *GetActorNameOrLabel());
    }
}

void AAeonCharacterBase::InitAbilityActorInfo()
{
    if (ensureMsgf(GetAbilitySystemComponent(),
                   TEXT("AbilitySystemComponent not configured on actor %s"),
                   *GetActorNameOrLabel()))
    {
        GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

        ensureMsgf(!CharacterStartUpData.IsNull(),
                   TEXT("AAeonCharacterBase::InitAbilityActorInfo: CharacterStartUpData not assigned to actor %s"),
                   *GetActorNameOrLabel());
    }
    else
    {
        AEON_ERROR_ALOG("AbilitySystemComponent not configured for actor %s", *GetActorNameOrLabel());
    }
}
