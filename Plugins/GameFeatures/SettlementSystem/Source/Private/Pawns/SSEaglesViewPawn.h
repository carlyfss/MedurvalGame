// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBCharacter.h"
#include "SSEaglesViewPawn.generated.h"

class UCBLineTraceComponent;
/**
 * 
 */
UCLASS()
class ASSEaglesViewPawn : public ACBCharacter
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float MovementSpeedDecelerationOffset = 1500.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float CameraSpeedOffset = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float CameraAccelerationMultiplier = 4.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float DefaultZoomDistance = 2000.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float ZoomSpeed = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float OrbitSpeed = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float MinZoomDistance = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float MaxZoomDistance = 4000.0f;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="EaglesView|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBLineTraceComponent> LineTraceComponent;

#pragma region Inputs
    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    UInputAction *ZoomInInput;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    UInputAction *ZoomOutInput;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    UInputAction *TurnRightInput;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    UInputAction *TurnLeftInput;

    void TurnRight(const FInputActionValue &Value);

    void CameraZoom(const FInputActionValue &Value);

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
#pragma endregion Inputs

public:
    ASSEaglesViewPawn();
};
