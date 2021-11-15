// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Consumables/BaseConsumableItemPrimaryDA.h"

FPrimaryAssetId UBaseConsumableItemPrimaryDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("ConsumableItem", GetFName());
}

void UBaseConsumableItemPrimaryDA::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);
	
	print("You used a consumable item");
}
