// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryAccessorySlotWidget.h"

void UMDInventoryAccessorySlotWidget::SetSlotAttachment(EMDAccessoryAttachment NewAttachment)
{
	Attachment = NewAttachment;
}

void UMDInventoryAccessorySlotWidget::SetSlotInfo(FMDInventoryAccessorySlot NewSlotInfo)
{
	Super::SetSlotInfo(NewSlotInfo, 0);
}
