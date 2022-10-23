// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "InputActionValue.h"
#include "MDDamageableCharacter.h"
#include "Core/Actors/Characters/MDCharacter.h"
#include "MDPlayerCharacter.generated.h"

class UMDActivatableWidget;
class UInputAction;
class UInputMappingContext;

UCLASS()
class MEDURVAL_API AMDPlayerCharacter : public AMDDamageableCharacter
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDPlayerCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDActivatableWidget> MainWidgetReference = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerCharacter|Inputs", meta=(AllowPrivateAccess=true))
    float DefaultRunSpeed = 350.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerCharacter|Inputs", meta=(AllowPrivateAccess=true))
    float TargetRunSpeed = 600.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerCharacter|Inputs", meta=(AllowPrivateAccess=true))
    float SpeedIncreaseByTick = 5.f;

    

protected:
    FTimerHandle RunTimerHandle;

#pragma region Inputs
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction* LookInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction* JumpInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction* InteractInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction* RunInputAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseCharacter|Inputs", meta = (AllowPrivateAccess = true))
    UInputAction* ToggleInventoryAction;
#pragma endregion Inputs

    void EnhancedLook(const FInputActionValue& Value);

    UFUNCTION(BlueprintImplementableEvent, Category="BaseCharacter|Inputs")
    void InteractWithObject() const;

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Inputs")
    void StartRunning();

    void IncreaseCharacterSpeed();

    void DecreaseCharacterSpeed();

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Inputs")
    void StopRunning();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BaseCharacter|Inputs")
    void ToggleInventory();
    
public:
    // Sets default values for this character's properties
    AMDPlayerCharacter();
    
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
    
};
