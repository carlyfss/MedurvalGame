// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDInventorySlotWidget.h"
#include "MDInventoryAccessorySlotWidget.generated.h"


UCLASS(meta = (DisplayName = "InventoryAccessorySlotWidget"))
class MEDURVAL_API UMDInventoryAccessorySlotWidget : public UMDInventorySlotWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="InventoryAccessorySlotWidget", meta=(AllowPrivateAccess=true))
	EMDAccessoryAttachment Attachment = EMDAccessoryAttachment::None;

public:
	UFUNCTION(BlueprintCallable, Category = "InventoryAccessorySlotWidget")
	void SetSlotAttachment(EMDAccessoryAttachment NewAttachment);

	void SetSlotInfo(FMDInventoryAccessorySlot NewSlotInfo);
};
