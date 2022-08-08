// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/SSSettlementEconomyComponent.h"

#include "Subsystems/CBCurrencySubsystem.h"

USSSettlementEconomyComponent::USSSettlementEconomyComponent()
{
}

void USSSettlementEconomyComponent::AddToTreasury(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->AddAmount(Treasury, Amount);
    UpdateTreasury();
}

void USSSettlementEconomyComponent::AddToIncome(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->AddAmount(TotalTreasuryIncome, Amount);
    IsToUpdateDailyChange = true;
    UpdateTreasury();
}

void USSSettlementEconomyComponent::AddToUpkeep(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->AddAmount(TotalTreasuryUpkeep, Amount);
    IsToUpdateDailyChange = true;
    UpdateTreasury();
}

void USSSettlementEconomyComponent::RemoveFromTreasury(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->RemoveAmount(Treasury, Amount);

    UpdateTreasury();
}

void USSSettlementEconomyComponent::UpdateTreasury()
{
    if (IsToUpdateDailyChange)
    {
        CalculateDailyChange();
        IsToUpdateDailyChange = false;
    }

    OnUpdateTresury.Broadcast();
}

void USSSettlementEconomyComponent::CalculateDailyChange()
{
    DailyChange = TotalTreasuryIncome - TotalTreasuryUpkeep;
}

void USSSettlementEconomyComponent::ChargeDailyChange()
{
    AddToTreasury(DailyChange);

    UpdateTreasury();
}
