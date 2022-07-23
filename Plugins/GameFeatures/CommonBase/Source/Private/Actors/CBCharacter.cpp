// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/CBCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/CBCameraComponent.h"
#include "Components/CBSpringArmComponent.h"
#include "Constants/CBConstants.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACBCharacter::PawnClientRestart()
{
    Super::PawnClientRestart();

    // Make sure that we have a valid PlayerController.
    if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
    {
        // Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
        if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<
            UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
            Subsystem->ClearAllMappings();

            // Add each mapping context, along with their priority values. Higher values outprioritize lower values.
            Subsystem->AddMappingContext(MappingContext, BaseMappingPriority);
        }
    }
}

void ACBCharacter::EnhancedMoveForward(const FInputActionValue &Value)
{
    if ((Controller != nullptr) && (Value.GetMagnitude() != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(Direction, Value.GetMagnitude());
    }
}

void ACBCharacter::EnhancedMoveRight(const FInputActionValue &Value)
{
    if ((Controller != nullptr) && (Value.GetMagnitude() != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, Value.GetMagnitude());
    }
}

// Sets default values
ACBCharacter::ACBCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.TickInterval = FCBConstants::TickInterval;

    GetCapsuleComponent()->PrimaryComponentTick.bCanEverTick = false;
    GetCapsuleComponent()->PrimaryComponentTick.bStartWithTickEnabled = false;

    // Configure Mesh
    GetMesh()->PrimaryComponentTick.bStartWithTickEnabled = false;
    GetMesh()->bPerBoneMotionBlur = false;
    GetMesh()->SetGenerateOverlapEvents(false);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;            // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // Additional settings
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // Setup SpringArmComponent
    SpringArmComponent = CreateDefaultSubobject<UCBSpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->TargetArmLength = 300.0f;
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->AddWorldOffset(FVector(0.0f, 0.0f, 50.0f));
    SpringArmComponent->SocketOffset = FVector(0.0f, 75.0f, 20.0f);

    // Setup CameraComponent
    CameraComponent = CreateDefaultSubobject<UCBCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->AddWorldRotation(FRotator(-5.0f, 0.0f, 0.0f));
}

void ACBCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    UEnhancedInputComponent *PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
    if (PlayerEnhancedInputComponent)
    {
        if (MoveForwardInput)
        {
            PlayerEnhancedInputComponent->BindAction(MoveForwardInput, ETriggerEvent::Triggered, this,
                                                     &ACBCharacter::EnhancedMoveForward);
        }

        if (MoveRightInput)
        {
            PlayerEnhancedInputComponent->BindAction(MoveRightInput, ETriggerEvent::Triggered, this,
                                                     &ACBCharacter::EnhancedMoveRight);
        }
    }
}

UEnhancedInputComponent *ACBCharacter::GetEnhancedInputComponent() const
{
    UEnhancedInputComponent *PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if (PlayerEnhancedInputComponent != nullptr)
    {
        return PlayerEnhancedInputComponent;
    }

    return nullptr;
}
