// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDWeaponDataAsset"))
class MEDURVAL_API UMDWeaponDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
