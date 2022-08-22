// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STMaintenanceComponent.h"
#include "Components/STSettlementComponent.h"

void USTMaintenanceComponent::SetDailyIncome(int Amount)
{
    DailyIncome = Amount;
}

void USTMaintenanceComponent::SetDailyUpkeep(int Amount)
{
    DailyUpkeep = Amount;
}

void USTMaintenanceComponent::SetCostToBuild(int Amount)
{
    CostToBuild = Amount;
}

int USTMaintenanceComponent::GetDailyIncome() const
{
    return DailyIncome;
}

int USTMaintenanceComponent::GetDailyUpkeep() const
{
    return DailyUpkeep;
}

int USTMaintenanceComponent::GetCostToBuild() const
{
    return CostToBuild;
}

void USTMaintenanceComponent::EnableMaintenance(USTSettlementComponent *Settlement)
{
    if (bIsMaintenanceEnabled)
        return;
    
    Settlement->GetEconomy()->AddToIncome(DailyIncome);
    Settlement->GetEconomy()->AddToUpkeep(DailyUpkeep);
    bIsMaintenanceEnabled = true;
}

void USTMaintenanceComponent::DisableMaintenance(USTSettlementComponent *Settlement)
{
    if (!bIsMaintenanceEnabled)
        return;
    
    Settlement->GetEconomy()->AddToIncome(DailyIncome * -1);
    Settlement->GetEconomy()->AddToUpkeep(DailyUpkeep * -1);
    bIsMaintenanceEnabled = false;
}
