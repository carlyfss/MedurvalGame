// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Enums/SSSettlementType.h"
#include "SSBuildingConstructionMeshes.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingConstructionMeshes"))
struct SETTLEMENTSYSTEM_API FSSBuildingConstructionMeshes
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingConstructionMeshes", meta=(AllowPrivateAccess=true))
    ESSSettlementType Civilization;

    /**
     * Construction meshes are going to be used in the order of the array
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingConstructionMeshes", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TArray<TSoftObjectPtr<UStaticMesh>> ConstructionMeshes;
};
