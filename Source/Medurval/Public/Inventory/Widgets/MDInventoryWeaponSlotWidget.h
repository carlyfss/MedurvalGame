// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDInventorySlotWidget.h"
#include "MDInventoryWeaponSlotWidget.generated.h"


UCLASS(meta = (DisplayName = "InventoryWeaponSlotWidget"))
class MEDURVAL_API UMDInventoryWeaponSlotWidget : public UMDInventorySlotWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="InventoryWeaponSlotWidget", meta=(AllowPrivateAccess=true))
	EMDWeaponAttachment Attachment = EMDWeaponAttachment::None;

public:
	UFUNCTION(BlueprintCallable, Category = "InventoryWeaponSlotWidget")
	void SetSlotAttachment(EMDWeaponAttachment NewAttachment);

	void SetSlotInfo(FMDInventoryWeaponSlot NewSlotInfo);
};
