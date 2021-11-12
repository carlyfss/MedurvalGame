// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/BaseInventoryWidget.h"

#include "BaseInventorySlotWidget.h"
#include "Components/InventoryComponent.h"

void UBaseInventoryWidget::SetInventoryReference(UInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UBaseInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}
