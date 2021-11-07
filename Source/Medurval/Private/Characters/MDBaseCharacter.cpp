// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "MDBaseCharacter.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Components/MDAbilitySystemComponent.h"
#include "Abilities/Components/MDBaseAttributeSet.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "Abilities/Enums/EMDGameplayAbilityInputID.h"
#include "Components/GameFrameworkComponentManager.h"
#include <GameplayEffectTypes.h>
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMDBaseCharacter::AMDBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

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
}

void AMDBaseCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
	
	UE_LOG(LogTemp, Warning, TEXT("Added receiver"))
}

// Called when the game starts or when spawned
void AMDBaseCharacter::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AMDBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
	
	Super::EndPlay(EndPlayReason);
}


void AMDBaseCharacter::MoveForward(const float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AMDBaseCharacter::MoveRight(const float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

UAbilitySystemComponent* AMDBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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

// Called to bind functionality to input
void AMDBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMDBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMDBaseCharacter::MoveRight);

	// Setup Binds for the Ability System
	if (AbilitySystemComponent && InputComponent)
	{
		int32 ConfirmBind = static_cast<int32>(EMDGameplayAbilityInputID::Confirm);
		int32 CancelBind = static_cast<int32>(EMDGameplayAbilityInputID::Cancel);

		const FString AbilityInputIDName = TEXT("EMDGameplayAbilityInputID");

		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", AbilityInputIDName, ConfirmBind, CancelBind);

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}
