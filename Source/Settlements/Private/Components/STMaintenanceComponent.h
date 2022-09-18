// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "STMaintenanceComponent.generated.h"

class USTSettlementComponent;

/**
 * 
 */
UCLASS()
class USTMaintenanceComponent : public UMDActorComponent
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="MaintenanceComponent", meta=(AllowPrivateAccess=true))
    int DailyIncome = 0;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="MaintenanceComponent", meta=(AllowPrivateAccess=true))
    int DailyUpkeep = 0;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="MaintenanceComponent", meta=(AllowPrivateAccess=true))
    int CostToBuild = 0;

    bool bIsMaintenanceEnabled = false;
    
public:
    USTMaintenanceComponent() {};
    
    void SetDailyIncome(int Amount);

    void SetDailyUpkeep(int Amount);

    void SetCostToBuild(int Amount);

    int GetDailyIncome() const;

    int GetDailyUpkeep() const;

    int GetCostToBuild() const;

    UFUNCTION(BlueprintCallable, Category="MaintenanceComponent")
    void EnableMaintenance(USTSettlementComponent *Settlement);

    UFUNCTION(BlueprintCallable, Category="MaintenanceComponent")
    void DisableMaintenance(USTSettlementComponent *Settlement);
};
