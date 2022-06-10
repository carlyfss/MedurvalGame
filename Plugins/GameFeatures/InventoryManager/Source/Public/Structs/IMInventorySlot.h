// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Items/_Base/IMBaseItemDA.h"
#include "IMInventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct INVENTORYMANAGER_API FIMInventorySlot
{
	GENERATED_BODY()

	FORCEINLINE FIMInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	TSoftObjectPtr<UIMBaseItemDA> ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	uint8 Amount = 0;
};

inline FIMInventorySlot::FIMInventorySlot()
{
	ItemData = nullptr;
	Amount = 0;
}
