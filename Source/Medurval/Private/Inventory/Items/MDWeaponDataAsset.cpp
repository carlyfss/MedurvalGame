// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDWeaponDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UMDWeaponDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::WeaponItemType, GetFName());
}
