// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAsset/CBPrimaryDataAsset.h"
#include "Enums/SSBuildingType.h"
#include "Enums/SSTerrainSize.h"
#include "Structs/SSBuildingTier.h"
#include "SSBuildingDA.generated.h"

class USSMaintenanceComponent;
/**
 * 
 */
UCLASS()
class USSBuildingDA : public UCBPrimaryDataAsset
{
    GENERATED_BODY()


public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BuildingDA|Configuration", AssetRegistrySearchable)
    FName BuildingRegistryTag = FName("Building");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    ESSTerrainSize Size = ESSTerrainSize::Small;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FName Name = FName("BuildingName");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    ESSBuildingType Type = ESSBuildingType::Civilian;

    /**
     * This actor is used to spawn in the world
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASSBuildingActor> BuildingClass;

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
    TArray<FSSBuildingTier> AvailableTiers;

    UPROPERTY(BlueprintReadWrite, Category="BuildingDA|Construction", meta=(AllowPrivateAccess=true))
    bool bIsAvailableToBuild = false;

    UPROPERTY(BlueprintReadWrite, Category="BuildingDA|Construction", meta=(AllowPrivateAccess=true))
    bool bIsUnderConstruction = false;
};
