// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "DataAssets/STBuildingDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId USTBuildingDA::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(UMedurvalAssetManager::SettlementBuildingType, GetFName());
}
