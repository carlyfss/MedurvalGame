// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "CBCharacter.generated.h"

class UMDLineTraceComponent;
class UCBCameraComponent;
class UCBSpringArmComponent;
struct FInputActionValue;

UCLASS()
class COMMONBASE_API ACBCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CBCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBSpringArmComponent> SpringArmComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CBCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBCameraComponent> CameraComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CBCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputMappingContext *MappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CBCharacter|Inputs", meta=(AllowPrivateAccess=true))
    int32 BaseMappingPriority = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CBCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputAction *MoveForwardInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CBCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputAction *MoveRightInput;

    virtual void PawnClientRestart() override;

protected:
    void EnhancedMoveForward(const FInputActionValue &Value);
    void EnhancedMoveRight(const FInputActionValue &Value);

public:
    ACBCharacter();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    FORCEINLINE class UCBSpringArmComponent *GetSpringArmComponent() const { return SpringArmComponent; }
    FORCEINLINE class UCBCameraComponent *GetCameraComponent() const { return CameraComponent; }

    UFUNCTION(BlueprintCallable, Category="CBCharacter|Inputs")
    UEnhancedInputComponent *GetEnhancedInputComponent() const;
};
