#include "Characters/EnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Misc/DataValidation.h"
#include "Widgets/WarriorWidgetBase.h"

AEnemyCharacter::AEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

    CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("CombatComponent");
    EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");
    EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
    // The world never occludes the widget
    EnemyHealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    // Render at the size requested by the widget
    EnemyHealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (const auto Widget = Cast<UWarriorWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
    {
        Widget->InitEnemyCreatedWidget(this);
    }
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    GiveStartUpDataToAbilitySystemAsync();
}

UPawnCombatComponent* AEnemyCharacter::GetPawnCombatComponent() const
{
    return CombatComponent;
}

UPawnUIComponent* AEnemyCharacter::GetPawnUIComponent() const
{
    return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacter::GetEnemyUIComponent() const
{
    return EnemyUIComponent;
}

#if WITH_EDITOR
EDataValidationResult AEnemyCharacter::IsDataValid(FDataValidationContext& Context) const
{
    const EDataValidationResult ExistingResult = Super::IsDataValid(Context);
    EDataValidationResult Result =
        (EDataValidationResult::NotValidated == ExistingResult) ? EDataValidationResult::Valid : ExistingResult;

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract) && !EnemyHealthWidgetComponent->GetWidgetClass())
    {
        const auto String = FString::Printf(TEXT("Object %s is not an abstract class but is missing the required "
                                                 "property HealthWidgetComponent.WidgetClass"),
                                            *GetActorNameOrLabel());
        Context.AddError(FText::FromString(String));
        Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
    }

    return Result;
}
#endif // WITH_EDITOR
