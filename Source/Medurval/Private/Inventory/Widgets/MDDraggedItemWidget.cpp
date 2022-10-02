// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDDraggedItemWidget.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "Core/Singletons/MDGameInstance.h"

void UMDDraggedItemWidget::SetInventoryReference(UMDInventoryComponent* InventoryRef)
{
	this->InventoryReference = InventoryRef;
}

void UMDDraggedItemWidget::SetSlotInfo(FMDInventorySlot NewSlotInfo)
{
	SlotInfo = NewSlotInfo;
	Item = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(SlotInfo.Item);
}
