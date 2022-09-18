// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STSettlementEconomyComponent.h"

USTSettlementEconomyComponent::USTSettlementEconomyComponent()
{
}

void USTSettlementEconomyComponent::SetStartingTreasury(int Amount)
{
    Treasury = Amount;
}

void USTSettlementEconomyComponent::AddToTreasury(int Amount)
{
    // UMDCurrencySubsystem *Subsystem = GetCurrencySubsystem();
    //
    // if (!Subsystem)
    //     return;
    //
    // Subsystem->AddAmount(Treasury, Amount);
    Treasury += Amount;
    
    UpdateTreasury();
}

void USTSettlementEconomyComponent::AddToIncome(int Amount)
{
    // UMDCurrencySubsystem *Subsystem = GetCurrencySubsystem();
    //
    // if (!Subsystem)
    //     return;
    //
    // Subsystem->AddAmount(TotalTreasuryIncome, Amount);
    TotalTreasuryIncome += Amount;
    IsToUpdateDailyChange = true;
    UpdateTreasury();
}

void USTSettlementEconomyComponent::AddToUpkeep(int Amount)
{
    // UMDCurrencySubsystem *Subsystem = GetCurrencySubsystem();
    //
    // if (!Subsystem)
    //     return;
    //
    // Subsystem->AddAmount(TotalTreasuryUpkeep, Amount);
    TotalTreasuryUpkeep += Amount;
    IsToUpdateDailyChange = true;
    UpdateTreasury();
}

void USTSettlementEconomyComponent::RemoveFromTreasury(int Amount)
{
    // UMDCurrencySubsystem *Subsystem = GetCurrencySubsystem();
    //
    // if (!Subsystem)
    //     return;
    //
    // Subsystem->RemoveAmount(Treasury, Amount);

    Treasury -= Amount;

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
