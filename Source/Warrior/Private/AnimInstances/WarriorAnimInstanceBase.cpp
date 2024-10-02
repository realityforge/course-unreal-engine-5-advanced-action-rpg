#include "AnimInstances/WarriorAnimInstanceBase.h"
#include "GameplayTagContainer.h"
#include "WarriorFunctionLibrary.h"

bool UWarriorAnimInstanceBase::IsTagPresentOnOwner(const FGameplayTag TagToCheck) const
{
    if (const auto OwningPawn = TryGetPawnOwner())
    {
        return UWarriorFunctionLibrary::NativeIsGameplayTagPresentOnActor(OwningPawn, TagToCheck);
    }
    else
    {
        return false;
    }
}
