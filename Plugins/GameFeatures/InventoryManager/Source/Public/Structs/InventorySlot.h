// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Items/InventoryItemDA.h"

#include "InventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct INVENTORYMANAGER_API FInventorySlot
{
	GENERATED_BODY()

	FORCEINLINE FInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot")
	TSoftClassPtr<UInventoryItemDA> ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot")
	int32 Amount = 0;
};

inline FInventorySlot::FInventorySlot()
{
	ItemData = UInventoryItemDA::StaticClass();
	Amount = 0;
}
