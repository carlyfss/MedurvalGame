// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/CBActorComponent.h"
#include "Subsystems/CBCurrencySubsystem.h"
#include "Constants/CommonBaseConstants.h"

UCBActorComponent::UCBActorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCommonBaseConstants::TickInterval;
}

UCBCurrencySubsystem *UCBActorComponent::GetCurrencySubsystem() const
{
    const UGameInstance *GameInstance = GetWorld()->GetGameInstance();

    if (!GameInstance)
        return nullptr;

    UCBCurrencySubsystem *Subsystem = GameInstance->GetSubsystem<UCBCurrencySubsystem>();

    return Subsystem;
}
