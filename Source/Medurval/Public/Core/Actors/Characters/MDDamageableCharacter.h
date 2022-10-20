// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "MDEnhancedCharacter.h"
#include "MDDamageableCharacter.generated.h"

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
class MEDURVAL_API AMDDamageableCharacter : public AMDEnhancedCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

#pragma region AbilitiesProps
	UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="BaseCharacter|Attributes")
	TArray<TSubclassOf<UMDBaseGameplayAbility>> DefaultAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attributes", meta=(AllowPrivateAccess=true))
	UMDAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Attributes", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDBaseAttributeSet> AttributeSetComponent = nullptr;
#pragma endregion AbilitiesProps

protected:
public:
	AMDDamageableCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PreInitializeComponents() override;

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
