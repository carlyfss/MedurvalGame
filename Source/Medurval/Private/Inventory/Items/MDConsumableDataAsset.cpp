// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDConsumableDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UMDConsumableDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::ConsumableItemType, GetFName());
}

void UMDConsumableDataAsset::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);
}
