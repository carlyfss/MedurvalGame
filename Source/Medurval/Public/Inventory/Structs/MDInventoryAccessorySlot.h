// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "MDInventorySlot.h"
#include "Inventory/Enums/MDAccessoryAttachment.h"
#include "MDInventoryAccessorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventoryEquipmentSlot"))
struct MEDURVAL_API FMDInventoryAccessorySlot : public FMDInventorySlot
{
	GENERATED_BODY()

	FMDInventoryAccessorySlot() : Attachment(EMDAccessoryAttachment::None)
	{
		Super();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryAccessorySlot")
	EMDAccessoryAttachment Attachment;
};
