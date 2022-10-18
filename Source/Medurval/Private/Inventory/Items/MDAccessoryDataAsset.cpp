// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDAccessoryDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

EMDAccessoryAttachment UMDAccessoryDataAsset::GetAccessoryAttachment()
{
	return Attachment;
}

FPrimaryAssetId UMDAccessoryDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::AccessoryItemType, GetFName());
}
