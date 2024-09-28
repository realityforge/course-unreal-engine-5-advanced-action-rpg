#pragma once

#include "Aeon/Controllers/AeonPlayerController.h"
#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "HeroPlayerController.generated.h"

UCLASS()
class WARRIOR_API AWarriorHeroPlayerController : public AAeonPlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

    FGenericTeamId HeroTeamID;

public:
    AWarriorHeroPlayerController();

#pragma region IGenericTeamAgentInterface Interface
    virtual FGenericTeamId GetGenericTeamId() const override;
#pragma endregion
};
