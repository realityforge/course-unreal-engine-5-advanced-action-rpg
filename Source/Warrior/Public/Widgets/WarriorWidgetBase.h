#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "WarriorWidgetBase.generated.h"

class UEnemyUIComponent;
class UHeroUIComponent;

/**
 * Base class for widgets in the Warrior project.
 */
UCLASS(Abstract)
class WARRIOR_API UWarriorWidgetBase : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
    void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
    void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:
    UFUNCTION(BlueprintCallable)
    void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
