// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Items/_Base/IMBaseItemDA.h"
#include "Engine/AssetManager.h"
#include "Interfaces/IMUsableItemInterface.h"

FPrimaryAssetId UIMBaseItemDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("DefaultItem", GetFName());
}

void UIMBaseItemDA::UseItem_Implementation(AActor* ItemOwner)
{
	IIMUsableItemInterface::UseItem_Implementation(ItemOwner);
}
