// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "MDBaseCharacter.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "EnhancedInputComponent.h"
#include "Abilities/Components/MDAbilitySystemComponent.h"
#include "Abilities/Components/MDBaseAttributeSet.h"
#include "Abilities/Components/MDBaseGameplayAbility.h"
#include "Abilities/Enums/EMDGameplayAbilityInputID.h"
#include "Components/GameFrameworkComponentManager.h"
#include <GameplayEffectTypes.h>
#include "Blueprint/UserWidget.h"
#include "Core/Components/Utils/MDLineTraceComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMDBaseCharacter::AMDBaseCharacter()
{
    // Setup Ability system component and replication mode
    AbilitySystemComponent = CreateDefaultSubobject<UMDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    /** Create an attribute component so the player can have those attributes
     *	Like Health, Stamina, etc... or any attributes in the AttributeSet */
    AttributeSetComponent = CreateDefaultSubobject<UMDBaseAttributeSet>(TEXT("AttributeSetComponent"));

    // Setup LineTraceComponent (Move to ACBCharacter class)
    LineTraceComponent = CreateDefaultSubobject<UMDLineTraceComponent>(TEXT("LineTraceComponent"));
}

#pragma region Overrides
void AMDBaseCharacter::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

// Called when the game starts or when spawned
void AMDBaseCharacter::BeginPlay()
{
    UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(
        this, UGameFrameworkComponentManager::NAME_GameActorReady);

    Super::BeginPlay();

    // Initialize Player Reference in MDGameInstance
    UMDGameInstance* GameInstance = Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (GameInstance)
    {
        ACharacter* PlayerRef = GameInstance->GetPlayerReference();
        if (!PlayerRef)
        {
            GameInstance->SetPlayerReference(this);
        }
    }
}

void AMDBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
}

void AMDBaseCharacter::StartRunning() const
{
    GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed + RunSpeedIncreaseAmount;  
}

void AMDBaseCharacter::StopRunning() const
{
    GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed - RunSpeedIncreaseAmount;
}

void AMDBaseCharacter::EnableLineTrace()
{
    LineTraceComponent->SetLineTraceEnabled(true);
}

void AMDBaseCharacter::DisableLineTrace()
{
    LineTraceComponent->SetLineTraceEnabled(false);
}

void AMDBaseCharacter::PossessedBy(AController *NewController)
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
UAbilitySystemComponent *AMDBaseCharacter::GetAbilitySystemComponent() const
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
        for (TSubclassOf<UMDBaseGameplayAbility> &StartupAbility : DefaultAbilities)
        {
            const int32 InputID = static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID);

            FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1, InputID, this);

            AbilitySystemComponent->GiveAbility(AbilitySpec);
        }
    }
}

void AMDBaseCharacter::GetHealth(float &Health, float &MaxHealth) const
{
    if (AttributeSetComponent)
    {
        Health = AttributeSetComponent->GetHealth();
        MaxHealth = AttributeSetComponent->GetMaxHealth();
    }
}

void AMDBaseCharacter::GetStamina(float &Stamina, float &MaxStamina) const
{
    if (AttributeSetComponent)
    {
        Stamina = AttributeSetComponent->GetStamina();
        MaxStamina = AttributeSetComponent->GetMaxStamina();
    }
}

void AMDBaseCharacter::GetMana(float &Mana, float &MaxMana) const
{
    if (AttributeSetComponent)
    {
        Mana = AttributeSetComponent->GetMana();
        MaxMana = AttributeSetComponent->GetMaxMana();
    }
}

#pragma endregion GameplayAbilityFunc

#pragma region Inputs

void AMDBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    UEnhancedInputComponent *PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
    if (PlayerEnhancedInputComponent)
    {
        if (LookInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this,
                                                     &AMDBaseCharacter::EnhancedLook);
        }

        if (InteractInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(InteractInputAction, ETriggerEvent::Started, this,
                                                     &AMDBaseCharacter::InteractWithObject);
        }

        if (JumpInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
            PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this,
                                                     &ACharacter::StopJumping);
        }

        if (RunInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Started, this, &AMDBaseCharacter::StartRunning);
            PlayerEnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Completed, this,
                                                     &AMDBaseCharacter::StopRunning);
        }

        if (ToggleInventoryAction)
        {
            PlayerEnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AMDBaseCharacter::ToggleInventory);
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

void AMDBaseCharacter::EnhancedLook(const FInputActionValue &Value)
{
    if (Value.GetMagnitude() != 0.0f)
    {
        AddControllerPitchInput(Value[1] * -1);
        AddControllerYawInput(Value[0]);
    }
}
#pragma endregion Inputs
