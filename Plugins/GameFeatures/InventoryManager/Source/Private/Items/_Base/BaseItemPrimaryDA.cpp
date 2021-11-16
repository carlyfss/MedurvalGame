// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/_Base/BaseItemPrimaryDA.h"

#include "Interfaces/UsableItemInterface.h"

FPrimaryAssetId UBaseItemPrimaryDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("DefaultItem", GetFName());
}

void UBaseItemPrimaryDA::UseItem_Implementation(AActor* ItemOwner)
{
	IUsableItemInterface::UseItem_Implementation(ItemOwner);
}
