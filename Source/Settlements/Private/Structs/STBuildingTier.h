// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "STBuildingConstructionMeshes.h"
#include "STBuildingRequirements.h"
#include "Enums/STCivilizationType.h"
#include "STBuildingTier.generated.h"

class UStaticMesh;

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingTier"))
struct SETTLEMENTS_API FSTBuildingTier
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|UI", meta=(AllowPrivateAccess=true))
    FText Description = FText::FromName("Tier description.");

    /**
     * Defines the Building mesh by Settlement Type
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Meshes", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TMap<ESTCivilizationType, TSoftObjectPtr<UStaticMesh>> CivilizationMesh;

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
    FSTBuildingRequirements Requirements;

    /**
     * Duration in seconds
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true, ClampMin="0", ClampMax="10000"))
    int ConstructionDuration = 5;

    /**
     * Delay to update the Construction Step.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true, ClampMin="1", ClampMax="5"))
    int ConstructionStepUpdateDelay = 1;

    /**
     * Defines construction meshes for each Settlement Type
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Construction", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TArray<FSTBuildingConstructionMeshes> ConstructionMeshes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    FText UnlockablesDescription = FText::FromName("Decription of what the tier unlocks.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Unlockableitems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier|Unlockables", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> UnlockableBuildings;

    
};