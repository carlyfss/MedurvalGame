// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/DraggedItemWidget.h"

UIMBaseItemDA* UDraggedItemWidget::GetItemInfo() const
{
	return ItemInfo;
}

void UDraggedItemWidget::SetItemInfo(UIMBaseItemDA* Item)
{
	this->ItemInfo = Item;
}

uint8 UDraggedItemWidget::GetAmount() const
{
	return Amount;
}

void UDraggedItemWidget::SetAmount(uint8 DraggedAmount)
{
	this->Amount = DraggedAmount;
}

UIMInventoryComponent* UDraggedItemWidget::GetInventoryReference() const
{
	return InventoryReference;
}

void UDraggedItemWidget::SetInventoryReference(UIMInventoryComponent* InventoryRef)
{
	this->InventoryReference = InventoryRef;
}
