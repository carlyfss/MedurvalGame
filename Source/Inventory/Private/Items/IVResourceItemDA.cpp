// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/IVResourceItemDA.h"

#include "Core/AssetManager/MedurvalAssetManager.h"


FPrimaryAssetId UIVResourceItemDA::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(UMedurvalAssetManager::ResourceItemType, GetFName());
}
