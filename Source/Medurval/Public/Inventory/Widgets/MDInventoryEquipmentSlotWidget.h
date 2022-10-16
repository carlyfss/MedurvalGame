// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonLazyImage.h"
#include "MDInventorySlotWidget.h"
#include "MDInventoryEquipmentSlotWidget.generated.h"


UCLASS(meta = (DisplayName = "InventoryEquipmentSlotWidget"))
class MEDURVAL_API UMDInventoryEquipmentSlotWidget : public UMDInventorySlotWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="InventoryEquipmentSlotWidget", meta=(AllowPrivateAccess=true))
	EMDEquipmentAttachment Attachment = EMDEquipmentAttachment::None;

public:
	UFUNCTION(BlueprintCallable, Category = "InventoryEquipmentSlotWidget")
	void SetSlotAttachment(EMDEquipmentAttachment NewAttachment);

	void SetSlotInfo(FMDInventoryEquipmentSlot NewSlotInfo);
};
