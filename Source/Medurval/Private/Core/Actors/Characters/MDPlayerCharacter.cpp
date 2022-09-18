// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Core/Actors/Characters/MDPlayerCharacter.h"

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
#include "Core/Singletons/MDGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMDPlayerCharacter::AMDPlayerCharacter()
{
    // Setup Ability system component and replication mode
    AbilitySystemComponent = CreateDefaultSubobject<UMDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    /** Create an attribute component so the player can have those attributes
     *	Like Health, Stamina, etc... or any attributes in the AttributeSet */
    AttributeSetComponent = CreateDefaultSubobject<UMDBaseAttributeSet>(TEXT("AttributeSetComponent"));
}

#pragma region Overrides
void AMDPlayerCharacter::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

// Called when the game starts or when spawned
void AMDPlayerCharacter::BeginPlay()
{
    UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(
        this, UGameFrameworkComponentManager::NAME_GameActorReady);

    Super::BeginPlay();

    // Initialize Player Reference in MDGameInstance
    AMDGameMode* GameMode = Cast<AMDGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        ACharacter* PlayerRef = GameMode->GetPlayerReference();
        if (!PlayerRef)
        {
            GameMode->SetPlayerReference(this);
        }
    }
}

void AMDPlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
}

void AMDPlayerCharacter::StartRunning() const
{
    GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed + RunSpeedIncreaseAmount;  
}

void AMDPlayerCharacter::StopRunning() const
{
    GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed - RunSpeedIncreaseAmount;
}

void AMDPlayerCharacter::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);

    // Server Ability System init
    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    InitializeAttributes();
    GiveAbilities();
}

void AMDPlayerCharacter::OnRep_PlayerState()
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
UAbilitySystemComponent *AMDPlayerCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AMDPlayerCharacter::InitializeAttributes()
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

void AMDPlayerCharacter::GiveAbilities()
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

void AMDPlayerCharacter::GetHealth(float &Health, float &MaxHealth) const
{
    if (AttributeSetComponent)
    {
        Health = AttributeSetComponent->GetHealth();
        MaxHealth = AttributeSetComponent->GetMaxHealth();
    }
}

void AMDPlayerCharacter::GetStamina(float &Stamina, float &MaxStamina) const
{
    if (AttributeSetComponent)
    {
        Stamina = AttributeSetComponent->GetStamina();
        MaxStamina = AttributeSetComponent->GetMaxStamina();
    }
}

void AMDPlayerCharacter::GetMana(float &Mana, float &MaxMana) const
{
    if (AttributeSetComponent)
    {
        Mana = AttributeSetComponent->GetMana();
        MaxMana = AttributeSetComponent->GetMaxMana();
    }
}

#pragma endregion GameplayAbilityFunc

#pragma region Inputs

void AMDPlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
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
                                                     &AMDPlayerCharacter::EnhancedLook);
        }

        if (InteractInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(InteractInputAction, ETriggerEvent::Started, this,
                                                     &AMDPlayerCharacter::InteractWithObject);
        }

        if (JumpInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
            PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this,
                                                     &ACharacter::StopJumping);
        }

        if (RunInputAction)
        {
            PlayerEnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Started, this, &AMDPlayerCharacter::StartRunning);
            PlayerEnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Completed, this,
                                                     &AMDPlayerCharacter::StopRunning);
        }

        if (ToggleInventoryAction)
        {
            PlayerEnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AMDPlayerCharacter::ToggleInventory);
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

void AMDPlayerCharacter::EnhancedLook(const FInputActionValue &Value)
{
    if (Value.GetMagnitude() != 0.0f)
    {
        AddControllerPitchInput(Value[1] * -1);
        AddControllerYawInput(Value[0]);
    }
}
#pragma endregion Inputs
