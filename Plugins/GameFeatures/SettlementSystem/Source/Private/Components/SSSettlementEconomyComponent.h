// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/CBActorComponent.h"
#include "SSSettlementEconomyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateTresury);

/**
 * 
 */
UCLASS()
class USSSettlementEconomyComponent : public UCBActorComponent
{
    GENERATED_BODY()

    USSSettlementEconomyComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementEconomyComponent", meta=(AllowPrivateAccess=true))
    int TotalTreasuryIncome;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementEconomyComponent", meta=(AllowPrivateAccess=true))
    int TotalTreasuryUpkeep;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementEconomyComponent", meta=(AllowPrivateAccess=true))
    int DailyChange;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementEconomyComponent", meta=(AllowPrivateAccess=true))
    int Treasury = 200;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementEconomyComponent", meta=(AllowPrivateAccess=true))
    int TreasuryLimit = 10000;

    bool IsToUpdateDailyChange = false;
    // SettlementTaxesComponent - Taxes

public:
    // AddToTreasury
    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void AddToTreasury(int Amount);

    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void AddToIncome(int Amount);

    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void AddToUpkeep(int Amount);

    // RemoveFromTreasury
    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void RemoveFromTreasury(int Amount);

    // UpdateTreasury
    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void UpdateTreasury();

    UPROPERTY(BlueprintAssignable)
    FOnUpdateTresury OnUpdateTresury;

    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void CalculateDailyChange();

    // UpdateDailyTreasury
    UFUNCTION(BlueprintCallable, Category="SettlementEconomyComponent")
    void ChargeDailyChange();
};