// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/DataAssets/MDPrimaryDataAsset.h"

FPrimaryAssetId UMDPrimaryDataAsset::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("MDPrimaryAsset", GetFName());
}
