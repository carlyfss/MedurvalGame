// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "GameFramework/Character.h"
#include "MDBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMDBaseGameplayAbility;
class UGameplayEffect;
class UMDBaseAttributeSet;
class UMDAbilitySystemComponent;

UCLASS()
class MEDURVAL_API AMDBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

	// BEGIN Ability system components
	UPROPERTY(EditDefaultsOnly, Category="Attributes|Defaults")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Attributes|Defaults")
	TArray<TSubclassOf<UMDBaseGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attriutes|Components", meta=(AllowPrivateAccess=true))
	UMDAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attriutes", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDBaseAttributeSet> AttributeSetComponent = nullptr;
	// END Ability system components

public:
	// Sets default values for this character's properties
	AMDBaseCharacter();

protected:
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

#pragma region AbilitySystem
	// Mandatory function for the Gameplay Ability system
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual void InitializeAttributes();

	virtual void GiveAbilities();
#pragma endregion AbilitySystem

	UFUNCTION(BlueprintCallable, Category="Getters")
	virtual void GetHealth(float& Health, float& MaxHealth) const;

	UFUNCTION(BlueprintCallable, Category="Getters")
	virtual void GetStamina(float& Stamina, float& MaxStamina) const;

	UFUNCTION(BlueprintCallable, Category="Getters")
	virtual void GetMana(float& Mana, float& MaxMana) const;

};


