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
    int DailyIncome;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="MaintenanceComponent", meta=(AllowPrivateAccess=true))
    int DailyUpkeep;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="MaintenanceComponent", meta=(AllowPrivateAccess=true))
    int CostToBuild;

public:
    void SetDailyIncome(int Amount);

    void SetDailyUpkeep(int Amount);

    void SetCostToBuild(int Amount);

    int GetDailyIncome() const;

    int GetDailyUpkeep() const;

    int GetCostToBuild() const;

    UFUNCTION(BlueprintCallable, Category="MaintenanceComponent")
    void EnableMaintenance(USSSettlementComponent *Settlement) const;

    UFUNCTION(BlueprintCallable, Category="MaintenanceComponent")
    void DisableMaintenance(USSSettlementComponent *Settlement) const;
};
