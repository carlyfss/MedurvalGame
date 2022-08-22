// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Consumables/IMConsumableItemDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Macros/PrintString.h"

FPrimaryAssetId UIMConsumableItemDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::ConsumableItemType, GetFName());
}

void UIMConsumableItemDA::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);
}
