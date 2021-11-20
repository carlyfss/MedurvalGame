// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Items/_Base/BaseItemPrimaryDA.h"
#include "IMInventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct INVENTORYMANAGER_API FIMInventorySlot
{
	GENERATED_BODY()

	FORCEINLINE FIMInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	TSoftObjectPtr<UBaseItemPrimaryDA> ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	uint8 Amount = 0;
};

inline FIMInventorySlot::FIMInventorySlot()
{
	ItemData = nullptr;
	Amount = 0;
}
