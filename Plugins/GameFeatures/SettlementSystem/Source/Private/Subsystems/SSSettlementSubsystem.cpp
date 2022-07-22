// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Subsystems/SSSettlementSubsystem.h"

#include "Components/SSSettlementComponent.h"
#include "GameFramework/Character.h"
#include "Subsystems/GameInstanceSubsystem.h"

void USSSettlementSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
}

void USSSettlementSubsystem::Deinitialize()
{
}

USSSettlementComponent *USSSettlementSubsystem::GetSettlementByOwner(ACharacter *OwnerCharacter) const
{
    USSSettlementComponent *ReturnedSettlement = nullptr;

    for (USSSettlementComponent *Settlement : Settlements)
    {
        if (Settlement->GetSettlementOwner() == OwnerCharacter)
        {
            ReturnedSettlement = Settlement;
        }
    }

    return ReturnedSettlement;
}

TArray<USSSettlementComponent *> USSSettlementSubsystem::GetSettlements() const
{
    return Settlements;
}

void USSSettlementSubsystem::RegisterNewSettlement(USSSettlementComponent *Settlement)
{
    if (!Settlement)
        return;

    Settlements.Add(Settlement);
}
