// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAsset/CBPrimaryDataAsset.h"
#include "Enums/SSBuildingType.h"
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

protected:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FGameplayTag SizeTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    FName Name = FName("BuildingName");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Configuration", meta=(AllowPrivateAccess=true))
    ESSBuildingType Type = ESSBuildingType::Civilian;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Tiers", meta=(AllowPrivateAccess=true))
    bool bHasTiers = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingDA|Tiers", meta=(AllowPrivateAccess=true))
    TArray<FSSBuildingTier> AvailableTiers;

    UPROPERTY(BlueprintReadWrite, Category="BuildingDA|Construction", meta=(AllowPrivateAccess=true))
    bool bIsAvailableToBuild = false;

    UPROPERTY(BlueprintReadWrite, Category="BuildingDA|Construction", meta=(AllowPrivateAccess=true))
    bool bIsUnderConstruction = false;
};
