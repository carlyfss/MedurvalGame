// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MDBaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Base attribute set class for the Gameplay Abilities System
 */
UCLASS(meta = (DisplayName = "MedurvalBaseAttributeSet"))
class MEDURVAL_API UMDBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMDBaseAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** 
	 * Health Properties
	 ********************************************/
#pragma region HealthProps
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Health", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMDBaseAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Health", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMDBaseAttributeSet, MaxHealth);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
#pragma endregion HealthProps

	/**
	 * Stamina Properties
	 ********************************************/
#pragma region StaminaProps
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stamina", ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UMDBaseAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stamina", ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UMDBaseAttributeSet, MaxStamina);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
#pragma endregion StaminaProps

	/**
	 * Mana Properties
	 ********************************************/
#pragma region ManaProps
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Mana", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMDBaseAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Mana", ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMDBaseAttributeSet, MaxMana);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
#pragma endregion ManaProps
};
