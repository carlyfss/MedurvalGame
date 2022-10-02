// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Inventory/Widgets/MDDetailWidget.h"

#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Items/MDItemDataAsset.h"

void UMDDetailWidget::SetSlotInfo(FMDInventorySlot NewSlotInfo)
{
	SlotInfo = NewSlotInfo;
	Item = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(SlotInfo.Item);	
}
