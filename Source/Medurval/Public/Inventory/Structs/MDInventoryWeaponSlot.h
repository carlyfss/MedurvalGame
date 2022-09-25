// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "Inventory/Items/MDWeaponDataAsset.h"
#include "MDInventoryWeaponSlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventoryEquipmentSlot"))
struct MEDURVAL_API FMDInventoryWeaponSlot
{
	GENERATED_BODY()

	FORCEINLINE FMDInventoryWeaponSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryEquipmentSlot")
	TObjectPtr<UMDWeaponDataAsset> Weapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventoryEquipmentSlot")
	EMDWeaponAttachment Attachment;
};

inline FMDInventoryWeaponSlot::FMDInventoryWeaponSlot()
{
	Weapon = nullptr;
	Attachment = EMDWeaponAttachment::None;
}
