#pragma once

#include "CoreMinimal.h"
#include "WarriorEnumTypes.generated.h"

UENUM()
enum class EWarriorConfirmType : uint8
{
    Yes,
    No
};

UENUM()
enum class EWarriorValidType : uint8
{
    Valid,
    Invalid
};
