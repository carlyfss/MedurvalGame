// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDAccessoryDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UMDAccessoryDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::EquipmentItemType, GetFName());
}
