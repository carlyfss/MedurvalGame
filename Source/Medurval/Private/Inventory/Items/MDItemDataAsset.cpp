// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDItemDataAsset.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Engine/AssetManager.h"
#include "Inventory/Interfaces/MDUsableItemInterface.h"

FPrimaryAssetId UMDItemDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::DefaultItemType, GetFName());
}

void UMDItemDataAsset::UseItem_Implementation(AActor* ItemOwner)
{
	IMDUsableItemInterface::UseItem_Implementation(ItemOwner);
}
