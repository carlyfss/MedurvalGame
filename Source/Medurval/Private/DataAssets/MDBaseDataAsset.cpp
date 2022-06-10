// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "DataAssets/MDBaseDataAsset.h"

#include "Core/Singleton/MDGameInstance.h"

void UMDBaseDataAsset::SetDataAssetOwner(AActor* AssetOwner)
{
	DataAssetOwner = AssetOwner;
}

TObjectPtr<UMDGameInstance> UMDBaseDataAsset::GetGameInstance()
{
	if (!GameInstance)
	{
		GameInstance = Cast<UMDGameInstance>(DataAssetOwner->GetWorld()->GetGameInstance());
		return GameInstance;
	}

	return GameInstance;
}
