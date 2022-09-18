// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "InputActionValue.h"
#include "Core/Actors/Characters/MDCharacter.h"
#include "MDPlayerCharacter.generated.h"

class UMDActivatableWidget;
class UMDCameraComponent;
class UMDSpringArmComponent;
class UMDLineTraceComponent;

class UMDBaseGameplayAbility;
class UGameplayEffect;
class UMDBaseAttributeSet;
class UMDAbilitySystemComponent;

class UInputAction;
class UInputMappingContext;

UCLASS()
class MEDURVAL_API AMDPlayerCharacter : public AMDCharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MDPlayerCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDLineTraceComponent> LineTraceComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDPlayerCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDActivatableWidget> MainWidgetReference = nullptr;

#pragma region AbilitiesProps
    UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes")
    TSubclassOf<UGameplayEffect> DefaultAttributeEffect = nullptr;

    UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes")
    TArray<TSubclassOf<UMDBaseGameplayAbility>> DefaultAbilities;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attributes", meta=(AllowPrivateAccess=true))
    UMDAbilitySystemComponent *AbilitySystemComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attributes", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBaseAttributeSet> AttributeSetComponent = nullptr;
#pragma endregion AbilitiesProps

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerCharacter|Inputs", meta=(AllowPrivateAccess=true))
    float RunSpeedIncreaseAmount = 300.f;

public:
    // Sets default values for this character's properties
    AMDPlayerCharacter();

protected:
    virtual void PreInitializeComponents() override;

    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

#pragma region Inputs
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction *LookInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction *JumpInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction *InteractInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
    UInputAction *RunInputAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseCharacter|Inputs", meta = (AllowPrivateAccess = true))
    UInputAction *ToggleInventoryAction;

    void EnhancedLook(const FInputActionValue &Value);

    UFUNCTION(BlueprintImplementableEvent, Category="BaseCharacter|Inputs")
    void InteractWithObject() const;

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Inputs")
    void StartRunning() const;

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Inputs")
    void StopRunning() const;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BaseCharacter|Inputs")
    void ToggleInventory();
#pragma endregion Inputs

public:
    void EnableLineTrace();

    void DisableLineTrace();

    virtual void PossessedBy(AController *NewController) override;

    virtual void OnRep_PlayerState() override;

#pragma region AbilitySystem
    // Mandatory function for the Gameplay Ability system
    virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

    virtual void InitializeAttributes();

    virtual void GiveAbilities();

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Getters")
    virtual void GetHealth(float &Health, float &MaxHealth) const;

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Getters")
    virtual void GetStamina(float &Stamina, float &MaxStamina) const;

    UFUNCTION(BlueprintCallable, Category="BaseCharacter|Getters")
    virtual void GetMana(float &Mana, float &MaxMana) const;
#pragma endregion AbilitySystem
};
