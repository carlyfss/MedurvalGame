// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Consumables/IMConsumableItemDA.h"

#include "Macros/PrintString.h"

FPrimaryAssetId UIMConsumableItemDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("ConsumableItem", GetFName());
}

void UIMConsumableItemDA::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);
}
