#pragma once

#include "Aeon/Components/AeonPawnComponentBase.h"
#include "CoreMinimal.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);

/**
 * Abstract component with UI related functionality that is shared between the Hero/Enemy classes.
 */
UCLASS(Abstract)
class WARRIOR_API UPawnUIComponent : public UAeonPawnComponentBase
{
    GENERATED_BODY()

    /** Delegate invoked when health changes. */
    UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = "true"))
    FOnPercentChangedDelegate OnCurrentHealthChanged;

public:
    FORCEINLINE const FOnPercentChangedDelegate& GetOnCurrentHealthChanged() const { return OnCurrentHealthChanged; }
};
