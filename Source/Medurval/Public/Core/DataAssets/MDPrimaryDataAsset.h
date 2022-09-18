// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MDPrimaryDataAsset.generated.h"

class UGameInstance;
/**
 * 
 */
UCLASS(meta=(DisplayName="MDPrimaryDataAsset"))
class MEDURVAL_API UMDPrimaryDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    /**
     * Always override this function on the child classes
     * Just return the new FPrimaryAssetId (Don't call super)
     * Template: return FPrimaryAssetId("MDPrimaryAsset", GetFName());
     */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

};
