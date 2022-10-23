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

AMDPlayerCharacter::AMDPlayerCharacter()
{
}

void AMDPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = DefaultRunSpeed;

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

void AMDPlayerCharacter::StartRunning()
{
    const FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AMDPlayerCharacter::IncreaseCharacterSpeed);
    GetWorld()->GetTimerManager().SetTimer(RunTimerHandle, Delegate, 0.01f, true, 0.f);
}

void AMDPlayerCharacter::IncreaseCharacterSpeed()
{
    if (GetCharacterMovement()->MaxWalkSpeed < TargetRunSpeed)
    {
        GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed + SpeedIncreaseByTick;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = TargetRunSpeed;
        GetWorldTimerManager().ClearTimer(RunTimerHandle);
        RunTimerHandle.Invalidate();
    }
}

void AMDPlayerCharacter::DecreaseCharacterSpeed()
{
    if (GetCharacterMovement()->MaxWalkSpeed > DefaultRunSpeed)
    {
        GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed - SpeedIncreaseByTick;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = DefaultRunSpeed;
        GetWorldTimerManager().ClearTimer(RunTimerHandle);
        RunTimerHandle.Invalidate();
    }
}

void AMDPlayerCharacter::StopRunning()
{
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();

    if (TimerManager.TimerExists(RunTimerHandle))
    {
        GetWorldTimerManager().ClearTimer(RunTimerHandle);
        RunTimerHandle.Invalidate();
    }

    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AMDPlayerCharacter::DecreaseCharacterSpeed);
    TimerManager.SetTimer(RunTimerHandle, Delegate, 0.01f, true);
}

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
}

void AMDPlayerCharacter::EnhancedLook(const FInputActionValue &Value)
{
    if (Value.GetMagnitude() != 0.0f)
    {
        AddControllerPitchInput(Value[1] * -1);
        AddControllerYawInput(Value[0]);
    }
}