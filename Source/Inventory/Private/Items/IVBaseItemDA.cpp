// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Items/IVBaseItemDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Engine/AssetManager.h"
#include "Interfaces/IVUsableItemInterface.h"

FPrimaryAssetId UIVBaseItemDA::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(UMedurvalAssetManager::DefaultItemType, GetFName());
}

void UIVBaseItemDA::UseItem_Implementation(AActor *ItemOwner)
{
    IIVUsableItemInterface::UseItem_Implementation(ItemOwner);
}
