// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Enums/STCivilizationType.h"
#include "STBuildingConstructionMeshes.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingConstructionMeshes"))
struct SETTLEMENTS_API FSTBuildingConstructionMeshes
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingConstructionMeshes", meta=(AllowPrivateAccess=true))
    ESTCivilizationType Civilization;

    /**
     * Construction meshes are going to be used in the order of the array
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingConstructionMeshes", meta=(AllowPrivateAccess=true, AssetBundles = "World"))
    TArray<TSoftObjectPtr<UStaticMesh>> Meshes;
};
