// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "MDInventorySlot.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "MDInventoryEquipmentSlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventoryEquipmentSlot"))
struct MEDURVAL_API FMDInventoryEquipmentSlot : public FMDInventorySlot
{
	GENERATED_BODY()

	FMDInventoryEquipmentSlot() : Attachment(EMDEquipmentAttachment::None)
	{
		Super();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryEquipmentSlot")
	EMDEquipmentAttachment Attachment;
};
