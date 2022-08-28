// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/IVConsumableItemDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UIVConsumableItemDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::ConsumableItemType, GetFName());
}

void UIVConsumableItemDA::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);
}
