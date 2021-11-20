﻿// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "MDBaseCharacter.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Abilities/Components/MDAbilitySystemComponent.h"
#include "Abilities/Components/MDBaseAttributeSet.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "Abilities/Enums/EMDGameplayAbilityInputID.h"
#include "Components/GameFrameworkComponentManager.h"
#include <GameplayEffectTypes.h>

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MDLineTraceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMDBaseCharacter::AMDBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickInterval = 0.075f;

	GetMesh()->PrimaryComponentTick.bStartWithTickEnabled = false;
	GetMesh()->bPerBoneMotionBlur = false;
	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetCapsuleComponent()->PrimaryComponentTick.bCanEverTick = false;
	GetCapsuleComponent()->PrimaryComponentTick.bStartWithTickEnabled = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Setup Ability system component and replication mode
	AbilitySystemComponent = CreateDefaultSubobject<UMDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	/** Create an attribute component so the player can have those attributes
	*	Like Health, Stamina, etc... or any attributes in the AttributeSet */
	AttributeSetComponent = CreateDefaultSubobject<UMDBaseAttributeSet>(TEXT("AttributeSetComponent"));

	LineTraceComponent = CreateDefaultSubobject<UMDLineTraceComponent>(TEXT("LineTraceComponent"));
}

#pragma region Overrides
void AMDBaseCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);

	UE_LOG(LogTemp, Warning, TEXT("Added receiver"))
}

// Called when the game starts or when spawned
void AMDBaseCharacter::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(
		this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AMDBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
}

void AMDBaseCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}
	}
}

void AMDBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server Ability System init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void AMDBaseCharacter::OnRep_PlayerState()
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
UAbilitySystemComponent* AMDBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMDBaseCharacter::InitializeAttributes()
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

void AMDBaseCharacter::GiveAbilities()
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

void AMDBaseCharacter::GetHealth(float& Health, float& MaxHealth) const
{
	if (AttributeSetComponent)
	{
		Health = AttributeSetComponent->GetHealth();
		MaxHealth = AttributeSetComponent->GetMaxHealth();
	}
}

void AMDBaseCharacter::GetStamina(float& Stamina, float& MaxStamina) const
{
	if (AttributeSetComponent)
	{
		Stamina = AttributeSetComponent->GetStamina();
		MaxStamina = AttributeSetComponent->GetMaxStamina();
	}
}

void AMDBaseCharacter::GetMana(float& Mana, float& MaxMana) const
{
	if (AttributeSetComponent)
	{
		Mana = AttributeSetComponent->GetMana();
		MaxMana = AttributeSetComponent->GetMaxMana();
	}
}

#pragma endregion GameplayAbilityFunc

#pragma region Inputs

UEnhancedInputComponent* AMDBaseCharacter::GetEnhancedInputComponent() const
{
	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (PlayerEnhancedInputComponent != nullptr)
	{
		return PlayerEnhancedInputComponent;	
	}

	return nullptr;
}

void AMDBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (PlayerEnhancedInputComponent)
	{
		if (MoveForwardInput)
		{
			PlayerEnhancedInputComponent->BindAction(MoveForwardInput, ETriggerEvent::Triggered, this, &AMDBaseCharacter::EnhancedMoveForward);
		}

		if (MoveRightInput)
		{
			PlayerEnhancedInputComponent->BindAction(MoveRightInput, ETriggerEvent::Triggered, this, &AMDBaseCharacter::EnhancedMoveRight);
		}
		
		if (LookInput)
		{
			PlayerEnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &AMDBaseCharacter::EnhancedLook);
		}

		if (InteractAction)
		{
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMDBaseCharacter::InteractWithObject);
		}
		
		if (JumpInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
	}
	
	// Setup Binds for the Ability System
	if (AbilitySystemComponent && InputComponent)
	{
		const int32 ConfirmBind = static_cast<int32>(EMDGameplayAbilityInputID::Confirm);
		const int32 CancelBind = static_cast<int32>(EMDGameplayAbilityInputID::Cancel);

		const FString AbilityInputIDName = TEXT("EMDGameplayAbilityInputID");

		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", AbilityInputIDName, ConfirmBind, CancelBind);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void AMDBaseCharacter::EnhancedMoveForward(const FInputActionValue& Value)
{
	if ((Controller != nullptr) && (Value.GetMagnitude() != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value.GetMagnitude());
	}
}

void AMDBaseCharacter::EnhancedMoveRight(const FInputActionValue& Value)
{
	if ((Controller != nullptr) && (Value.GetMagnitude() != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value.GetMagnitude());
	}
}

void AMDBaseCharacter::EnhancedLook(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.0f)
	{
		AddControllerPitchInput(Value[1] * -1);
		AddControllerYawInput(Value[0]);	
	}
}
#pragma endregion Inputs
