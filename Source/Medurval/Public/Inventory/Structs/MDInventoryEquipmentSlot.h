// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Items/MDEquipmentDataAsset.h"
#include "MDInventoryEquipmentSlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventoryEquipmentSlot"))
struct MEDURVAL_API FMDInventoryEquipmentSlot
{
	GENERATED_BODY()

	FORCEINLINE FMDInventoryEquipmentSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryEquipmentSlot")
	TObjectPtr<UMDEquipmentDataAsset> Equipment = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryEquipmentSlot")
	EMDEquipmentAttachment Attachment;
};

inline FMDInventoryEquipmentSlot::FMDInventoryEquipmentSlot()
{
	Equipment = nullptr;
	Attachment = EMDEquipmentAttachment::None;
}
