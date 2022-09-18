// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "MDCharacter.generated.h"

class UMDLineTraceComponent;
class UMDCameraComponent;
class UMDSpringArmComponent;
struct FInputActionValue;

UCLASS()
class MEDURVAL_API AMDCharacter : public ACharacter
{
    GENERATED_BODY()

    // UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDCharacter|Components", meta=(AllowPrivateAccess=true))
    // TObjectPtr<UMDLineTraceComponent> LineTraceComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSpringArmComponent> SpringArmComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDCameraComponent> CameraComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputMappingContext *MappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    int32 BaseMappingPriority = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputAction *MoveForwardInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputAction *MoveRightInput;

    virtual void PawnClientRestart() override;

protected:
    void EnhancedMoveForward(const FInputActionValue &Value);
    void EnhancedMoveRight(const FInputActionValue &Value);

public:
    AMDCharacter();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

    FORCEINLINE UMDSpringArmComponent *GetSpringArmComponent() const { return SpringArmComponent; }
    FORCEINLINE UMDCameraComponent *GetCameraComponent() const { return CameraComponent; }

    // void EnableLineTrace() const;
    //
    // void DisableLineTrace() const;
};