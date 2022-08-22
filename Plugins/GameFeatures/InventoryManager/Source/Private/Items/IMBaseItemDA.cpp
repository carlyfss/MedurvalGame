// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Items/IMBaseItemDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Engine/AssetManager.h"
#include "Interfaces/IMUsableItemInterface.h"

FPrimaryAssetId UIMBaseItemDA::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(UMedurvalAssetManager::DefaultItemType, GetFName());
}

void UIMBaseItemDA::UseItem_Implementation(AActor *ItemOwner)
{
    IIMUsableItemInterface::UseItem_Implementation(ItemOwner);
}
