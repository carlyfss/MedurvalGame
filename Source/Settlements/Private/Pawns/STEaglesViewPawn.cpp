// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Pawns/STEaglesViewPawn.h"

#include "EnhancedInputComponent.h"
#include "Components/CBLineTraceComponent.h"
#include "Components/CBSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ASTEaglesViewPawn::ASTEaglesViewPawn()
{
    this->GetSpringArmComponent()->TargetArmLength = DefaultZoomDistance;

    LineTraceComponent = CreateDefaultSubobject<UCBLineTraceComponent>("LineTraceComponent");
}

void ASTEaglesViewPawn::TurnRight(const FInputActionValue &Value)
{
    if ((Controller != nullptr) && (Value.GetMagnitude() != 0.0f))
    {
        const float OrbitSpeeCalculation = Value.GetMagnitude() * OrbitSpeed;
        AddControllerYawInput(OrbitSpeeCalculation);
    }
}

void ASTEaglesViewPawn::CameraZoom(const FInputActionValue &Value)
{
    if (this->GetSpringArmComponent() && Value.GetMagnitude() != 0.0f)
    {
        const float ZoomSpeedCalculation = Value.GetMagnitude() * ZoomSpeed;
        const float CurrentSpringArmLength = this->GetSpringArmComponent()->TargetArmLength;

        const float FinalLength = CurrentSpringArmLength + ZoomSpeedCalculation;
        this->GetSpringArmComponent()->TargetArmLength = FMath::Clamp(FinalLength, MinZoomDistance, MaxZoomDistance);

        this->GetCharacterMovement()->MaxFlySpeed = FinalLength + CameraSpeedOffset;
        this->GetCharacterMovement()->BrakingDecelerationFlying = FinalLength + MovementSpeedDecelerationOffset;
        this->GetCharacterMovement()->MaxAcceleration = FinalLength * CameraAccelerationMultiplier;
    }
}

void ASTEaglesViewPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    UEnhancedInputComponent *PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
    if (PlayerEnhancedInputComponent)
    {
        if (ZoomInInput)
        {
            PlayerEnhancedInputComponent->BindAction(ZoomInInput, ETriggerEvent::Triggered, this,
                                                     &ASTEaglesViewPawn::CameraZoom);
        }

        if (ZoomOutInput)
        {
            PlayerEnhancedInputComponent->BindAction(ZoomOutInput, ETriggerEvent::Triggered, this,
                                                     &ASTEaglesViewPawn::CameraZoom);
        }

        if (TurnLeftInput)
        {
            PlayerEnhancedInputComponent->BindAction(TurnLeftInput, ETriggerEvent::Triggered, this,
                                                     &ASTEaglesViewPawn::TurnRight);
        }

        if (TurnRightInput)
        {
            PlayerEnhancedInputComponent->BindAction(TurnRightInput, ETriggerEvent::Triggered, this,
                                                     &ASTEaglesViewPawn::TurnRight);
        }
    }
}