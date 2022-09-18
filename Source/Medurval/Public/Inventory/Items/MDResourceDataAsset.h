// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDResourceDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDResourceDataAsset"))
class MEDURVAL_API UMDResourceDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
