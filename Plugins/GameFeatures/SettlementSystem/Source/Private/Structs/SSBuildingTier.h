// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "SSBuildingRequirements.h"
#include "Enums/SSSettlementStages.h"
#include "SSBuildingTier.generated.h"

class ASSBuildingActor;
class UStaticMesh;

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingTier"))
struct SETTLEMENTSYSTEM_API FSSBuildingTier
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|UI", meta=(AllowPrivateAccess=true))
    FText Description = FText::FromName("Tier description.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Meshes", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TSoftObjectPtr<UStaticMesh> Mesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Meshes", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TMap<ESSSettlementStages, TSoftObjectPtr<UStaticMesh>> StageMeshes;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true))
    uint8 ConstructionSteps;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TArray<TSoftObjectPtr<UStaticMesh>> UnderConstructionMeshes;

    /**
     * Construction duration in seconds
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true))
    uint8 ConstructionDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|UI", meta=(AllowPrivateAccess=true, AssetBundles = "UI"))
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Economy", meta=(AllowPrivateAccess=true))
    int DailyIncome;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Economy", meta=(AllowPrivateAccess=true))
    int DailyUpkeep;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Economy", meta=(AllowPrivateAccess=true))
    int CostToBuild;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    FText UnlockablesDescription = FText::FromName("Decription of what the tier unlocks.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Unlockableitems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> UnlockableBuildings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Requirements", meta=(AllowPrivateAccess=true))
    FSSBuildingRequirements Requirements;
};
