// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDEquipmentDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDEquipmentDataAsset"))
class MEDURVAL_API UMDEquipmentDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
