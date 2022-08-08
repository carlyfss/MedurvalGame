// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSSettlementComponent.h"
#include "Components/CBActorComponent.h"
#include "SSMaintenanceComponent.generated.h"

class USSSettlementComponent;

/**
 * 
 */
UCLASS()
class USSMaintenanceComponent : public UCBActorComponent
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
    void SetDailyIncome(int Amount);

    void SetDailyUpkeep(int Amount);

    void SetCostToBuild(int Amount);

    int GetDailyIncome() const;

    int GetDailyUpkeep() const;

    int GetCostToBuild() const;

    UFUNCTION(BlueprintCallable, Category="MaintenanceComponent")
    void EnableMaintenance(USSSettlementComponent *Settlement);

    UFUNCTION(BlueprintCallable, Category="MaintenanceComponent")
    void DisableMaintenance(USSSettlementComponent *Settlement);
};
