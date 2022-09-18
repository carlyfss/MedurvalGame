// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/DataAssets/MDPrimaryDataAsset.h"
#include "Enums/STBuildingType.h"
#include "Enums/STTerrainSize.h"
#include "Structs/STBuildingTier.h"
#include "STBuildingDA.generated.h"

class USTMaintenanceComponent;
class ASTBuildingActor;
/**
 * 
 */
UCLASS()
class USTBuildingDA : public UMDPrimaryDataAsset
{
    GENERATED_BODY()


public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BuildingDA|Configuration", AssetRegistrySearchable)
    FName BuildingRegistryTag = FName("Building");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    ESTTerrainSize Size = ESTTerrainSize::Small;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FName Name = FName("BuildingName");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    ESTBuildingType Type = ESTBuildingType::Civilian;

    /**
     * This actor is used to spawn in the world
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASTBuildingActor> BuildingClass;

    /**
     * Does this building has more than one tier?
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Tiers", meta=(AllowPrivateAccess=true))
    bool bHasTiers = false;

    /**
     * Is this building exclusive to any Settlement Type?
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Tiers", meta=(AllowPrivateAccess=true))
    bool bIsAvailableForManyCivilizations = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Tiers", meta=(AllowPrivateAccess=true))
    TArray<FSTBuildingTier> AvailableTiers;

    UPROPERTY(BlueprintReadWrite, Category="BuildingDA|Construction", meta=(AllowPrivateAccess=true))
    bool bIsAvailableToBuild = false;

    UPROPERTY(BlueprintReadWrite, Category="BuildingDA|Construction", meta=(AllowPrivateAccess=true))
    bool bIsUnderConstruction = false;
};
