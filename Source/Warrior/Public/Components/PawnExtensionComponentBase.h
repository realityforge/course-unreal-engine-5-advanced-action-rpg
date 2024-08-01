#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PawnExtensionComponentBase.generated.h"

/**
 * Abstract class that is the based for (most) custom components within the project.
 */
UCLASS(Abstract, ClassGroup = (Warrior), meta = (BlueprintSpawnableComponent))
class WARRIOR_API UPawnExtensionComponentBase : public UActorComponent
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
