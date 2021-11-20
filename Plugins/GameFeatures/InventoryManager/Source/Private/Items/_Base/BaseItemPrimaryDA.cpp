// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/_Base/BaseItemPrimaryDA.h"

#include "Interfaces/IMUsableItemInterface.h"

FPrimaryAssetId UBaseItemPrimaryDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("DefaultItem", GetFName());
}

void UBaseItemPrimaryDA::UseItem_Implementation(AActor* ItemOwner)
{
	IIMUsableItemInterface::UseItem_Implementation(ItemOwner);
}
