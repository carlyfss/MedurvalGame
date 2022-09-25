// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDInventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct MEDURVAL_API FMDInventorySlot
{
	GENERATED_BODY()

	FORCEINLINE FMDInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlot")
	TObjectPtr<UMDItemDataAsset> Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlot")
	uint8 Amount = 0;
};

inline FMDInventorySlot::FMDInventorySlot()
{
	Item = nullptr;
	Amount = 0;
}
