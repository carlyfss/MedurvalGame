// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMDraggedItemWidget.h"

UIMBaseItemDA* UIMDraggedItemWidget::GetItemInfo() const
{
	return ItemInfo;
}

void UIMDraggedItemWidget::SetItemInfo(UIMBaseItemDA* Item)
{
	this->ItemInfo = Item;
}

uint8 UIMDraggedItemWidget::GetAmount() const
{
	return Amount;
}

void UIMDraggedItemWidget::SetAmount(uint8 DraggedAmount)
{
	this->Amount = DraggedAmount;
}

UIMInventoryComponent* UIMDraggedItemWidget::GetInventoryReference() const
{
	return InventoryReference;
}

void UIMDraggedItemWidget::SetInventoryReference(UIMInventoryComponent* InventoryRef)
{
	this->InventoryReference = InventoryRef;
}
