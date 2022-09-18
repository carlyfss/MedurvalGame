// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Widgets/IVInventoryWidget.h"
#include "Widgets/IVInventorySlotWidget.h"
#include "Components/IVInventoryComponent.h"

TArray<UIVInventorySlotWidget *> UIVInventoryWidget::GetSlotWidgets()
{
	return SlotWidgets;
}

void UIVInventoryWidget::SetInventoryReference(UIVInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UIVInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}

void UIVInventoryWidget::UpdateSlotAtIndex(uint8 SlotIndex)
{
	UIVInventorySlotWidget *SlotWidget = GetSlotWidgets()[SlotIndex];
	FIVInventorySlot TargetSlot = InventoryReference->GetSlots()[SlotIndex];

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