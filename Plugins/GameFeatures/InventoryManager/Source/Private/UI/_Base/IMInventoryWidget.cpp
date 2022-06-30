// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "UI/_Base/IMInventoryWidget.h"
#include "UI/_Base/IMInventorySlotWidget.h"
#include "Components/IMInventoryComponent.h"

TArray<UIMInventorySlotWidget *> UIMInventoryWidget::GetSlotWidgets()
{
	return SlotWidgets;
}

void UIMInventoryWidget::SetInventoryReference(UIMInventoryComponent *InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UIMInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}

void UIMInventoryWidget::UpdateSlotAtIndex(uint8 SlotIndex)
{
	UIMInventorySlotWidget *SlotWidget = GetSlotWidgets()[SlotIndex];
	FIMInventorySlot TargetSlot = InventoryReference->GetInventorySlots()[SlotIndex];

	SlotWidget->SetWidgetProperties(TargetSlot.Item, TargetSlot.Amount, SlotIndex);

	if (SlotWidget->GetAmount() > 0)
	{
		SlotWidget->UpdateSlot();
	}

	SlotWidget->CleanSlot();
}