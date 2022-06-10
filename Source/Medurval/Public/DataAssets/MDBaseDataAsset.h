// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/MDDataAssetInterface.h"

#include "MDBaseDataAsset.generated.h"

class UMDGameInstance;
UCLASS()
class MEDURVAL_API UMDBaseDataAsset : public UPrimaryDataAsset, public IMDDataAssetInterface
{
	GENERATED_BODY()

	TObjectPtr<AActor> DataAssetOwner = nullptr;

protected:
	TObjectPtr<UMDGameInstance> GameInstance = nullptr;

public:
	void SetDataAssetOwner(AActor* AssetOwner);

	TObjectPtr<UMDGameInstance> GetGameInstance();
};
