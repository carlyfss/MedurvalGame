// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "DataAssets/SSBuildingDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId USSBuildingDA::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("SettlementBuilding", GetFName());
}
