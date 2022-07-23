// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "DataAsset/CBPrimaryDataAsset.h"
#include "Engine/GameInstance.h"

FPrimaryAssetId UCBPrimaryDataAsset::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("CommonBaseAsset", GetFName());
}

void UCBPrimaryDataAsset::SetDataAssetOwner(AActor *AssetOwner)
{
    DataAssetOwner = AssetOwner;
}

TObjectPtr<UGameInstance> UCBPrimaryDataAsset::GetGameInstance()
{
    if (!GameInstance)
    {
        GameInstance = Cast<UGameInstance>(DataAssetOwner->GetWorld()->GetGameInstance());
        return GameInstance;
    }

    return GameInstance;
}
