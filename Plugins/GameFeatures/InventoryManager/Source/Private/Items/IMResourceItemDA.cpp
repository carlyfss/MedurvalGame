// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/IMResourceItemDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"


FPrimaryAssetId UIMResourceItemDA::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(UMedurvalAssetManager::ResourceItemType, GetFName());
}
