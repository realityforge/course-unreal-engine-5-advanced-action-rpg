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

// TODO: Migrate to Aeon?
UENUM()
enum class EWarriorSuccessType : uint8
{
    Successful,
    Failed
};
