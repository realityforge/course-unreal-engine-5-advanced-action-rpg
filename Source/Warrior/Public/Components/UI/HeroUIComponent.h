#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate,
                                            TSoftObjectPtr<UTexture2D>,
                                            SoftWeaponIcon);

/**
 * Component with UI related functionality for the hero.
 */
UCLASS()
class WARRIOR_API UHeroUIComponent : public UPawnUIComponent
{
    GENERATED_BODY()

    /** Delegate invoked when rage changes. */
    UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
    FOnPercentChangedDelegate OnCurrentRageChanged;

    /** Delegate invoked when the currently equipped weapon changes. */
    UPROPERTY(BlueprintCallable, BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
    FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;

public:
    FORCEINLINE const FOnPercentChangedDelegate& GetOnCurrentRageChanged() const { return OnCurrentRageChanged; }
};
