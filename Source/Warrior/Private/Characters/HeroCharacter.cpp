#include "Characters/HeroCharacter.h"
#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "Aeon/Input/AeonInputComponent.h"
#include "Aeon/Input/AeonInputConfig.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WarriorGameplayTags.h"

AHeroCharacter::AHeroCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength = 200.f;
    CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 400.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    CombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("CombatComponent"));
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    GiveStartUpDataToAbilitySystem();
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset has not been defined"));

    const auto LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
    const auto Subsystem = LocalPlayer ? LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>() : nullptr;
    check(Subsystem);

    Subsystem->AddMappingContext(InputConfigDataAsset->GetDefaultMappingContext(), 0);

    const auto AeonInputComponent = CastChecked<UAeonInputComponent>(PlayerInputComponent);

    AeonInputComponent->BindNativeInputAction(InputConfigDataAsset,
                                              WarriorGameplayTags::Input_Native_Move,
                                              ETriggerEvent::Triggered,
                                              this,
                                              &AHeroCharacter::Input_Move);
    AeonInputComponent->BindNativeInputAction(InputConfigDataAsset,
                                              WarriorGameplayTags::Input_Native_Look,
                                              ETriggerEvent::Triggered,
                                              this,
                                              &AHeroCharacter::Input_Look);

    AeonInputComponent->BindAbilityInputAction(InputConfigDataAsset,
                                               this,
                                               &AHeroCharacter::Input_AbilityInputPressed,
                                               &AHeroCharacter::Input_AbilityInputReleased);
}

void AHeroCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
    const FVector2D& MovementVector = InputActionValue.Get<FVector2D>();
    const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

    if (0.f != MovementVector.Y)
    {
        AddMovementInput(MovementRotation.RotateVector(FVector::ForwardVector), MovementVector.Y);
    }
    if (0.f != MovementVector.X)
    {
        AddMovementInput(MovementRotation.RotateVector(FVector::RightVector), MovementVector.X);
    }
}

void AHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
    const FVector2D& LookAxisVector = InputActionValue.Get<FVector2D>();
    if (0.f != LookAxisVector.X)
    {
        AddControllerYawInput(LookAxisVector.X);
    }
    if (0.f != LookAxisVector.Y)
    {
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AHeroCharacter::Input_AbilityInputPressed(const FGameplayTag InGameplayTag)
{
    GetAeonAbilitySystemComponent()->OnAbilityInputPressed(InGameplayTag);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AHeroCharacter::Input_AbilityInputReleased(const FGameplayTag InGameplayTag)
{
    GetAeonAbilitySystemComponent()->OnAbilityInputReleased(InGameplayTag);
}
