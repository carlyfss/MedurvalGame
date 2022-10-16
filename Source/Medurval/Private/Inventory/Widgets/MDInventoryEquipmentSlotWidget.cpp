// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryEquipmentSlotWidget.h"

void UMDInventoryEquipmentSlotWidget::SetSlotAttachment(EMDEquipmentAttachment NewAttachment)
{
	Attachment = NewAttachment;
}

void UMDInventoryEquipmentSlotWidget::SetSlotInfo(FMDInventoryEquipmentSlot NewSlotInfo)
{
	Super::SetSlotInfo(NewSlotInfo, 0);
}
