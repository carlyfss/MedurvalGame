﻿// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "InputActionValue.h"
#include "Actors/CBCharacter.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_BaseCharacter|Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBSpringArmComponent> SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_BaseCharacter|Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBCameraComponent> CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_BaseCharacter|Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDLineTraceComponent> LineTraceComponent = nullptr;

#pragma region AbilitiesProps
	UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes|Defaults")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes|Defaults")
	TArray<TSubclassOf<UMDBaseGameplayAbility>> DefaultAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attriutes|Components", meta=(AllowPrivateAccess=true))
	UMDAbilitySystemComponent* AbilitySystemComponent = nullptr;

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

	virtual void PawnClientRestart() override;

#pragma region Inputs
	// Input actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	UInputAction* MoveForwardInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	UInputAction* MoveRightInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	UInputAction* LookInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_BaseCharacter|Inputs")
	int32 BaseMappingPriority = 0;
	
	void EnhancedMoveForward(const FInputActionValue& Value);
	void EnhancedMoveRight(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent, Category="_BaseCharacter|Inputs")
	void InteractWithObject() const;
#pragma endregion Inputs

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class UCBSpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCBCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

#pragma region AbilitySystem
	// Mandatory function for the Gameplay Ability system
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void InitializeAttributes();

	virtual void GiveAbilities();

	UFUNCTION(BlueprintCallable, Category="BaseCharacter|Getters")
	virtual void GetHealth(float& Health, float& MaxHealth) const;

	UFUNCTION(BlueprintCallable, Category="BaseCharacter|Getters")
	virtual void GetStamina(float& Stamina, float& MaxStamina) const;

	UFUNCTION(BlueprintCallable, Category="BaseCharacter|Getters")
	virtual void GetMana(float& Mana, float& MaxMana) const;
#pragma endregion AbilitySystem

	UFUNCTION(BlueprintCallable, Category="_BaseCharacter|Inputs")
	UEnhancedInputComponent* GetEnhancedInputComponent() const;
};
