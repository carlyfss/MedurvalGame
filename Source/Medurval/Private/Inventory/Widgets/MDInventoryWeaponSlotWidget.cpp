// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryWeaponSlotWidget.h"

void UMDInventoryWeaponSlotWidget::SetSlotAttachment(EMDWeaponAttachment NewAttachment)
{
	Attachment = NewAttachment;
}

void UMDInventoryWeaponSlotWidget::SetSlotInfo(FMDInventoryWeaponSlot NewSlotInfo)
{
	Super::SetSlotInfo(NewSlotInfo, 0);
}
