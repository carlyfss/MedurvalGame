// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Enums/STTerrainSize.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "STSettlementSubsystem.generated.h"

class ASTTerrainActor;
class USTSettlementComponent;
/**
 *
 */
UCLASS(DisplayName = "SettlementSubsystem")
class SETTLEMENTS_API USTSettlementSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

    void OnSettlementBuildingsLoaded();

    TArray<TObjectPtr<USTSettlementComponent>> Settlements;

    TArray<FPrimaryAssetId> AllBuildings;

    TArray<TObjectPtr<ASTTerrainActor>> AllTerrains;

    TMap<FPrimaryAssetId, ESTTerrainSize> BuildingsMapBySize;

public:
    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    USTSettlementComponent *GetSettlementByOwner(ACharacter *OwnerCharacter) const;

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    TArray<USTSettlementComponent *> GetSettlements() const;

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    void RegisterNewSettlement(USTSettlementComponent *Settlement);

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    TMap<FPrimaryAssetId, ESTTerrainSize> GetBuildingsMapBySize() const;

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    TArray<FPrimaryAssetId> GetAllBuildings() const;

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    void AddNewTerrain(ASTTerrainActor *NewTerrain);

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    TArray<ASTTerrainActor*> GetAllTerrains() const;
};
