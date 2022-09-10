// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STSettlementEconomyComponent.h"
#include "Subsystems/CBCurrencySubsystem.h"

USTSettlementEconomyComponent::USTSettlementEconomyComponent()
{
}

void USTSettlementEconomyComponent::SetStartingTreasury(int Amount)
{
    Treasury = Amount;
}

void USTSettlementEconomyComponent::AddToTreasury(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->AddAmount(Treasury, Amount);
    UpdateTreasury();
}

void USTSettlementEconomyComponent::AddToIncome(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->AddAmount(TotalTreasuryIncome, Amount);
    IsToUpdateDailyChange = true;
    UpdateTreasury();
}

void USTSettlementEconomyComponent::AddToUpkeep(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->AddAmount(TotalTreasuryUpkeep, Amount);
    IsToUpdateDailyChange = true;
    UpdateTreasury();
}

void USTSettlementEconomyComponent::RemoveFromTreasury(int Amount)
{
    UCBCurrencySubsystem *Subsystem = GetCurrencySubsystem();

    if (!Subsystem)
        return;

    Subsystem->RemoveAmount(Treasury, Amount);

    UpdateTreasury();
}

void USTSettlementEconomyComponent::UpdateTreasury()
{
    if (IsToUpdateDailyChange)
    {
        CalculateDailyChange();
        IsToUpdateDailyChange = false;
    }

    OnUpdateTresury.Broadcast();
}

void USTSettlementEconomyComponent::CalculateDailyChange()
{
    DailyChange = TotalTreasuryIncome - TotalTreasuryUpkeep;
}

void USTSettlementEconomyComponent::ChargeDailyChange()
{
    AddToTreasury(DailyChange);

    UpdateTreasury();
}
