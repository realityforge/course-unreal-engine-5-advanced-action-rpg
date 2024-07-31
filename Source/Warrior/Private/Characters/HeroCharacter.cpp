#include "Characters/HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Input/WarriorInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
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
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset has not been defined"));

    const auto LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
    const auto Subsystem = LocalPlayer ? LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>() : nullptr;
    check(Subsystem);

    Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

    const auto WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);

    WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset,
                                                 WarriorGameplayTags::InputTag_Move,
                                                 ETriggerEvent::Triggered,
                                                 this,
                                                 &AHeroCharacter::Input_Move);
    WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset,
                                                 WarriorGameplayTags::InputTag_Look,
                                                 ETriggerEvent::Triggered,
                                                 this,
                                                 &AHeroCharacter::Input_Look);
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
