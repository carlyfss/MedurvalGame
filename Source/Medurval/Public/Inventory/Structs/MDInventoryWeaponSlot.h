// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "Inventory/Items/MDWeaponDataAsset.h"
#include "MDInventoryWeaponSlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventoryEquipmentSlot"))
struct MEDURVAL_API FMDInventoryWeaponSlot : public FMDInventorySlot
{
	GENERATED_BODY()

	FMDInventoryWeaponSlot() : Attachment(EMDWeaponAttachment::None)
	{
		Super();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryEquipmentSlot")
	EMDWeaponAttachment Attachment;
};