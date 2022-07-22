// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSBuildingActor.h"

#include "Components/CBStaticMeshComponent.h"
#include "Components/SSMaintenanceComponent.h"

ASSBuildingActor::ASSBuildingActor()
{
    Mesh = CreateDefaultSubobject<UCBStaticMeshComponent>("BuildingMesh");
    Maintenance = CreateDefaultSubobject<USSMaintenanceComponent>("MaintenanceComponent");
}

void ASSBuildingActor::OnConstructionCompleted()
{
    Maintenance->EnableMaintenance(AssignedSettlement);
}

void ASSBuildingActor::BeginPlay()
{
    Super::BeginPlay();

    if (AvailableTiers.Num() > 0)
    {
        CurrentTier = AvailableTiers[0];
        Maintenance->SetDailyIncome(CurrentTier.DailyIncome);
        Maintenance->SetDailyUpkeep(CurrentTier.DailyUpkeep);
        Maintenance->SetCostToBuild(CurrentTier.CostToBuild);
    }
}
