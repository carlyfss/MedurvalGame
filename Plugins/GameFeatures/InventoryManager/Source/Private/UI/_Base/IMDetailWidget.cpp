// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMDetailWidget.h"

UIMBaseItemDA* UIMDetailWidget::GetItemInfo() const
{
	return this->ItemInfo;
}

void UIMDetailWidget::SetItemInfo(UIMBaseItemDA* Item)
{
	this->ItemInfo = Item;
}
