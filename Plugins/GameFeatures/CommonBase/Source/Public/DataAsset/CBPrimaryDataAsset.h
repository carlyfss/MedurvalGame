// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBPrimaryDataAsset.generated.h"

class UGameInstance;
/**
 * 
 */
UCLASS(meta=(DisplayName="CBPrimaryDataAsset"))
class COMMONBASE_API UCBPrimaryDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

    TObjectPtr<AActor> DataAssetOwner = nullptr;

protected:
    TObjectPtr<UGameInstance> GameInstance = nullptr;

    /**
     * Always override this function on the child classes
     * Just return the new FPrimaryAssetId (Don't call super)
     */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
    void SetDataAssetOwner(AActor *AssetOwner);

    TObjectPtr<UGameInstance> GetGameInstance();
};
