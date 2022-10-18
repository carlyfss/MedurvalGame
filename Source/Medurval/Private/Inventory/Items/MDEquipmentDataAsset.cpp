// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDEquipmentDataAsset.h"

#include "Core/AssetManager/MedurvalAssetManager.h"

EMDEquipmentAttachment UMDEquipmentDataAsset::GetEquipmentAttachment()
{
	return Attachment;
}

FPrimaryAssetId UMDEquipmentDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::EquipmentItemType, GetFName());
}
