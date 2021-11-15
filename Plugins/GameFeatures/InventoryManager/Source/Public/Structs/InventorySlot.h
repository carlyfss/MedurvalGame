﻿// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Items/_Base/BaseItemPrimaryDA.h"
#include "InventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct INVENTORYMANAGER_API FInventorySlot
{
	GENERATED_BODY()

	FORCEINLINE FInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	TSoftObjectPtr<UBaseItemPrimaryDA> ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	uint8 Amount = 0;
};

inline FInventorySlot::FInventorySlot()
{
	ItemData = nullptr;
	Amount = 0;
}
