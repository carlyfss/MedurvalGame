// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Inventory/Widgets/MDDraggedItemWidget.h"

UMDItemDataAsset* UMDDraggedItemWidget::GetItemInfo() const
{
	return ItemInfo;
}

void UMDDraggedItemWidget::SetItemInfo(UMDItemDataAsset* Item)
{
	this->ItemInfo = Item;
}

uint8 UMDDraggedItemWidget::GetAmount() const
{
	return Amount;
}

void UMDDraggedItemWidget::SetAmount(uint8 DraggedAmount)
{
	this->Amount = DraggedAmount;
}

UMDInventoryComponent* UMDDraggedItemWidget::GetInventoryReference() const
{
	return InventoryReference;
}

void UMDDraggedItemWidget::SetInventoryReference(UMDInventoryComponent* InventoryRef)
{
	this->InventoryReference = InventoryRef;
}
