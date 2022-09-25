// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDEquipmentDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UMDEquipmentDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::EquipmentItemType, GetFName());
}
