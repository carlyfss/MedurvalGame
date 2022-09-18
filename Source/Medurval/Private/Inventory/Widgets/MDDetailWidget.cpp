// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Inventory/Widgets/MDDetailWidget.h"
#include "Inventory/Items/MDItemDataAsset.h"

UMDItemDataAsset* UMDDetailWidget::GetItemInfo() const
{
	return this->ItemInfo;
}

void UMDDetailWidget::SetItemInfo(UMDItemDataAsset* Item)
{
	this->ItemInfo = Item;
}
