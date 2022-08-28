// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/IVDraggedItemWidget.h"

UIVBaseItemDA* UIVDraggedItemWidget::GetItemInfo() const
{
	return ItemInfo;
}

void UIVDraggedItemWidget::SetItemInfo(UIVBaseItemDA* Item)
{
	this->ItemInfo = Item;
}

uint8 UIVDraggedItemWidget::GetAmount() const
{
	return Amount;
}

void UIVDraggedItemWidget::SetAmount(uint8 DraggedAmount)
{
	this->Amount = DraggedAmount;
}

UIVInventoryComponent* UIVDraggedItemWidget::GetInventoryReference() const
{
	return InventoryReference;
}

void UIVDraggedItemWidget::SetInventoryReference(UIVInventoryComponent* InventoryRef)
{
	this->InventoryReference = InventoryRef;
}
