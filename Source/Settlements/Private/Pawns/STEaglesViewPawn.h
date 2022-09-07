// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBCharacter.h"
#include "Widgets/STSettlementManagementWidget.h"
#include "STEaglesViewPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEaglesViewPossessed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEaglesViewUnpossessed);

class UMDLineTraceComponent;
/**
 * 
 */
UCLASS()
class ASTEaglesViewPawn : public ACBCharacter
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
    TObjectPtr<UMDLineTraceComponent> LineTraceComponent = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="EaglesView|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementManagementWidget> SettlementWidget = nullptr;

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
    ASTEaglesViewPawn();

    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnEaglesViewPossessed OnEaglesViewPossessed;

    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnEaglesViewUnpossessed OnEaglesViewUnpossessed;
};

