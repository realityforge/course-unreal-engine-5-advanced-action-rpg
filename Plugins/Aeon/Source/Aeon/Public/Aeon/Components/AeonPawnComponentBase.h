#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "AeonPawnComponentBase.generated.h"

/**
 * Abstract class that is the base class for (most) custom components within Aeon.
 */
UCLASS(Abstract, ClassGroup = (Aeon), meta = (BlueprintSpawnableComponent))
class AEON_API UAeonPawnComponentBase : public UActorComponent
{
    GENERATED_BODY()

protected:
    template <class T>
    FORCEINLINE T* GetOwningPawn() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,
                      "'T' template parameter in GetOwningPawn MUST be derived from APawn");
        return CastChecked<T>(GetOwner());
    }

    FORCEINLINE APawn* GetOwningPawn() const { return GetOwningPawn<APawn>(); }

    template <class T>
    T* GetOwningController() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
                      "'T' template parameter in GetOwningController MUST be derived from AController");
        return GetOwningPawn()->GetController<T>();
    }
};
