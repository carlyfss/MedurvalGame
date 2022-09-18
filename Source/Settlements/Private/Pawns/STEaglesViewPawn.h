// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Actors/Characters/MDCharacter.h"
#include "Widgets/STSettlementManagementWidget.h"
#include "STEaglesViewPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEaglesViewPossessed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEaglesViewUnpossessed);

class UMDLineTraceComponent;
/**
 * 
 */
UCLASS()
class ASTEaglesViewPawn : public AMDCharacter
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float MovementSpeedDecelerationOffset = 1500.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float CameraSpeedOffset = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float CameraAccelerationMultiplier = 4.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float DefaultZoomDistance = 4000.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float ZoomSpeed = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float OrbitSpeed = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float MinZoomDistance = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category="EaglesView|Inputs")
    float MaxZoomDistance = 6500.0f;

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

    float GetMaxZoomDistance() const;

    UFUNCTION(BlueprintCallable, Category="EaglesView")
    void EnableLineTrace();

    UFUNCTION(BlueprintCallable, Category="EaglesView")
    void DisableLineTrace();

    UFUNCTION(BlueprintCallable, Category="EaglesView")
    void SetSettlementWidget(UCommonActivatableWidget *Widget);

    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnEaglesViewPossessed OnEaglesViewPossessed;

    UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnEaglesViewUnpossessed OnEaglesViewUnpossessed;
};

