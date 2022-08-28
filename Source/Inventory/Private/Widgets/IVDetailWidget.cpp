// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/IVDetailWidget.h"
#include "Items/IVBaseItemDA.h"

UIVBaseItemDA* UIVDetailWidget::GetItemInfo() const
{
	return this->ItemInfo;
}

void UIVDetailWidget::SetItemInfo(UIVBaseItemDA* Item)
{
	this->ItemInfo = Item;
}
