// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "InputActionValue.h"
#include "Actors/CBCharacter.h"
#include "Widgets/MDMainWidget.h"
#include "MDBaseCharacter.generated.h"

class UCBCameraComponent;
class UCBSpringArmComponent;
class UMDLineTraceComponent;

class UMDBaseGameplayAbility;
class UGameplayEffect;
class UMDBaseAttributeSet;
class UMDAbilitySystemComponent;

class UInputAction;
class UInputMappingContext;

UCLASS()
class MEDURVAL_API AMDBaseCharacter : public ACBCharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CBCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDLineTraceComponent> LineTraceComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CBCharacter|Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDMainWidget> MainWidgetReference = nullptr;

#pragma region AbilitiesProps
    UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes|Defaults")
    TSubclassOf<UGameplayEffect> DefaultAttributeEffect = nullptr;

    UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes|Defaults")
    TArray<TSubclassOf<UMDBaseGameplayAbility>> DefaultAbilities;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attriutes|Components", meta=(AllowPrivateAccess=true))
    UMDAbilitySystemComponent *AbilitySystemComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attriutes", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBaseAttributeSet> AttributeSetComponent = nullptr;
#pragma endregion AbilitiesProps

public:
    // Sets default values for this character's properties
    AMDBaseCharacter();

protected:
    virtual void PreInitializeComponents() override;

    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

#pragma region Inputs
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
    UInputAction *LookInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
    UInputAction *JumpInputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
    UInputAction *InteractAction;

    void EnhancedLook(const FInputActionValue &Value);

    UFUNCTION(BlueprintImplementableEvent, Category="_BaseCharacter|Inputs")
    void InteractWithObject() const;
#pragma endregion Inputs

public:
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
