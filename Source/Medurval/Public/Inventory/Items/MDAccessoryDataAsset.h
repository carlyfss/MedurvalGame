// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDAccessoryDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDEquipmentDataAsset"))
class MEDURVAL_API UMDAccessoryDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
