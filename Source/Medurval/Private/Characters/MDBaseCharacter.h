// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MDBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UMDBaseGameplayAbility;
class UGameplayEffect;
class UMDBaseAttributeSet;
class UMDAbilitySystemComponent;

class UInputAction;
class UInputMappingContext;

UCLASS()
class MEDURVAL_API AMDBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
	UInputAction* MoveForwardInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
	UInputAction* MoveRightInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
	UInputAction* LookInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BaseCharacter|Inputs")
	int32 BaseMappingPriority = 0;
	
	void EnhancedMoveForward(const FInputActionValue& Value);
	void EnhancedMoveRight(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);
#pragma endregion Inputs

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
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
	
};
