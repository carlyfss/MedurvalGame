// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "SSBuildingRequirements.h"
#include "SSBuildingTier.generated.h"

class ASSBuildingActor;
class UStaticMesh;

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingTier"))
struct SETTLEMENTSYSTEM_API FSSBuildingTier
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    FName Name = FName("Tier Name");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    FText Description = FText::FromName("Tier description.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    TObjectPtr<UStaticMesh> Mesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    uint8 ConstructionSteps;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    TArray<UStaticMesh *> UnderConstructionMeshes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    TObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    uint8 ConstructionDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    FText UnlockablesDescription = FText::FromName("Decription of what the tier unlocks.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    TArray<UPrimaryDataAsset *> Unlockableitems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    TArray<ASSBuildingActor *> UnlockableBuildings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingTier", meta=(AllowPrivateAccess=true))
    FSSBuildingRequirements Requirements;
};
