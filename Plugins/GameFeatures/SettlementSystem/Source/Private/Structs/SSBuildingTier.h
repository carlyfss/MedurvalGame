// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "SSBuildingConstructionMeshes.h"
#include "SSBuildingRequirements.h"
#include "Enums/SSCivilizationType.h"
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

    /**
     * Defines the Building mesh by Settlement Type
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Meshes", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TMap<ESSCivilizationType, TSoftObjectPtr<UStaticMesh>> CivilizationMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|UI", meta=(AllowPrivateAccess=true, AssetBundles = "UI"))
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Economy", meta=(AllowPrivateAccess=true))
    int DailyIncome = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Economy", meta=(AllowPrivateAccess=true))
    int DailyUpkeep = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Economy", meta=(AllowPrivateAccess=true))
    int CostToBuild = 0;

    /**
     * Items needed for construction
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Requirements", meta=(AllowPrivateAccess=true))
    FSSBuildingRequirements Requirements;

    /**
     * Duration in seconds
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true, ClampMin="0", ClampMax="10000"))
    int ConstructionDuration = 5;

    /**
     * Defines construction meshes for each Settlement Type
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TArray<FSSBuildingConstructionMeshes> ConstructionMeshes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    FText UnlockablesDescription = FText::FromName("Decription of what the tier unlocks.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Unlockableitems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> UnlockableBuildings;

    
};