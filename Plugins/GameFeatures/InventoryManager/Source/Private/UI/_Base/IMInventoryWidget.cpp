// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMInventoryWidget.h"
#include "UI/_Base/IMInventorySlotWidget.h"
#include "Components/IMInventoryComponent.h"

TArray<UIMInventorySlotWidget*> UIMInventoryWidget::GetSlotWidgets()
{
	return SlotWidgets;
}

void UIMInventoryWidget::SetInventoryReference(UIMInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UIMInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}
