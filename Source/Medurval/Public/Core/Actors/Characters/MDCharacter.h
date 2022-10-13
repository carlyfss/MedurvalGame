// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Core/Components/MDSkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "MDCharacter.generated.h"

class AMDPlayerController;
class UMDGameInstance;
class UMDLineTraceComponent;
class UMDCameraComponent;
class UMDSpringArmComponent;
struct FInputActionValue;

UCLASS()
class MEDURVAL_API AMDCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputMappingContext *MappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    int32 BaseMappingPriority = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputAction *MoveForwardInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    UInputAction *MoveRightInput;

#pragma region EquipmentSlots
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> HelmetSlot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> ChestSlot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> GlovesSlot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> PantsSlot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> BootsSlot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> ShoulderSlot;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSkeletalMeshComponent> BeltSlot;
#pragma endregion EquipmentSlots

    virtual void PawnClientRestart() override;

    void GenerateEquipmentMeshSlots();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDLineTraceComponent> LineTraceComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSpringArmComponent> SpringArmComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDCameraComponent> CameraComponent = nullptr;
    
    void EnhancedMoveForward(const FInputActionValue &Value);
    
    void EnhancedMoveRight(const FInputActionValue &Value);

public:
    AMDCharacter();

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

    FORCEINLINE UMDSpringArmComponent *GetSpringArmComponent() const { return SpringArmComponent; }
    FORCEINLINE UMDCameraComponent *GetCameraComponent() const { return CameraComponent; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDCharacter")
    UMDGameInstance* GetMDGameInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDCharacter")
    AMDPlayerController* GetMDPlayerController() const;

    UFUNCTION(BlueprintCallable, Category="MDCharacter")
    void EnableLineTrace() const;

    UFUNCTION(BlueprintCallable, Category="MDCharacter")
    void DisableLineTrace() const;
};
