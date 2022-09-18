// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryWidget.h"
#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Inventory/Components/MDInventoryComponent.h"

TArray<UMDInventorySlotWidget*> UMDInventoryWidget::GetSlotWidgets()
{
	return SlotWidgets;
}

void UMDInventoryWidget::SetInventoryReference(UMDInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UMDInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}

void UMDInventoryWidget::UpdateSlotAtIndex(uint8 SlotIndex)
{
	UMDInventorySlotWidget* SlotWidget = GetSlotWidgets()[SlotIndex];
	FMDInventorySlot TargetSlot = InventoryReference->GetSlots()[SlotIndex];

	if (InventoryReference->IsSlotEmpty(SlotIndex))
	{
		SlotWidget->CleanSlot();
	}
	else
	{
		SlotWidget->SetWidgetProperties(TargetSlot.Item, TargetSlot.Amount, SlotIndex);
		SlotWidget->UpdateSlot();
	}
}
