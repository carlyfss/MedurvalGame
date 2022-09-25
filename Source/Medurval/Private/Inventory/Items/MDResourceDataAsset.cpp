// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDResourceDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UMDResourceDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::ResourceItemType, GetFName());
}
