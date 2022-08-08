// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/SSMaintenanceComponent.h"
#include "Components/SSSettlementComponent.h"

void USSMaintenanceComponent::SetDailyIncome(int Amount)
{
    DailyIncome = Amount;
}

void USSMaintenanceComponent::SetDailyUpkeep(int Amount)
{
    DailyUpkeep = Amount;
}

void USSMaintenanceComponent::SetCostToBuild(int Amount)
{
    CostToBuild = Amount;
}

int USSMaintenanceComponent::GetDailyIncome() const
{
    return DailyIncome;
}

int USSMaintenanceComponent::GetDailyUpkeep() const
{
    return DailyUpkeep;
}

int USSMaintenanceComponent::GetCostToBuild() const
{
    return CostToBuild;
}

void USSMaintenanceComponent::EnableMaintenance(USSSettlementComponent *Settlement)
{
    if (bIsMaintenanceEnabled)
        return;
    
    Settlement->GetEconomy()->AddToIncome(DailyIncome);
    Settlement->GetEconomy()->AddToUpkeep(DailyUpkeep);
    bIsMaintenanceEnabled = true;
}

void USSMaintenanceComponent::DisableMaintenance(USSSettlementComponent *Settlement)
{
    if (!bIsMaintenanceEnabled)
        return;
    
    Settlement->GetEconomy()->AddToIncome(DailyIncome * -1);
    Settlement->GetEconomy()->AddToUpkeep(DailyUpkeep * -1);
    bIsMaintenanceEnabled = false;
}
