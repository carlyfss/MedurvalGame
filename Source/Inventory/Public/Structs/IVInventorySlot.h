// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Items/IVBaseItemDA.h"
#include "IVInventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct INVENTORY_API FIVInventorySlot
{
	GENERATED_BODY()

	FORCEINLINE FIVInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	TObjectPtr<UIVBaseItemDA> Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Slot")
	uint8 Amount = 0;
};

inline FIVInventorySlot::FIVInventorySlot()
{
	Item = nullptr;
	Amount = 0;
}
