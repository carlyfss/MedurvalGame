﻿// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Core/Actors/Characters/MDDamageableCharacter.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Components/MDAbilitySystemComponent.h"
#include "Abilities/Components/MDBaseAttributeSet.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "Abilities/Enums/EMDGameplayAbilityInputID.h"
#include "Components/GameFrameworkComponentManager.h"
#include <GameplayEffectTypes.h>

#include "Blueprint/UserWidget.h"
#include "Core/Components/Utils/MDLineTraceComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Core/Singletons/MDGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMDDamageableCharacter::AMDDamageableCharacter()
{
	// Setup Ability system component and replication mode
	AbilitySystemComponent = CreateDefaultSubobject<UMDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	/** Create an attribute component so the player can have those attributes
	 *	Like Health, Stamina, etc... or any attributes in the AttributeSet */
	AttributeSetComponent = CreateDefaultSubobject<UMDBaseAttributeSet>(TEXT("AttributeSetComponent"));
}

void AMDDamageableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent && InputComponent)
	{
		const int32 ConfirmBind = static_cast<int32>(EMDGameplayAbilityInputID::Confirm);
		const int32 CancelBind = static_cast<int32>(EMDGameplayAbilityInputID::Cancel);

		const FString AbilityInputIDName = TEXT("EMDGameplayAbilityInputID");

		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", AbilityInputIDName, ConfirmBind, CancelBind);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

#pragma region Overrides
void AMDDamageableCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}


void AMDDamageableCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server Ability System init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void AMDDamageableCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client Ability System init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();

	// Setup Binds for the Ability System
	if (AbilitySystemComponent && InputComponent)
	{
		constexpr int32 ConfirmBind = static_cast<int32>(EMDGameplayAbilityInputID::Confirm);
		constexpr int32 CancelBind = static_cast<int32>(EMDGameplayAbilityInputID::Cancel);

		const FString AbilityInputIDName = TEXT("EMDGameplayAbilityInputID");

		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", AbilityInputIDName, ConfirmBind, CancelBind);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}
#pragma endregion Overrides

#pragma region GameplayAbilityFunc
UAbilitySystemComponent* AMDDamageableCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMDDamageableCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			DefaultAttributeEffect, 1, EffectContextHandle);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
		}
	}
}

void AMDDamageableCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UMDBaseGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			const int32 InputID = static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID);

			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1, InputID, this);

			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void AMDDamageableCharacter::GetHealth(float& Health, float& MaxHealth) const
{
	if (AttributeSetComponent)
	{
		Health = AttributeSetComponent->GetHealth();
		MaxHealth = AttributeSetComponent->GetMaxHealth();
	}
}

void AMDDamageableCharacter::GetStamina(float& Stamina, float& MaxStamina) const
{
	if (AttributeSetComponent)
	{
		Stamina = AttributeSetComponent->GetStamina();
		MaxStamina = AttributeSetComponent->GetMaxStamina();
	}
}

void AMDDamageableCharacter::GetMana(float& Mana, float& MaxMana) const
{
	if (AttributeSetComponent)
	{
		Mana = AttributeSetComponent->GetMana();
		MaxMana = AttributeSetComponent->GetMaxMana();
	}
}

#pragma endregion GameplayAbilityFunc