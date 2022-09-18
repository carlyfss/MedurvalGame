// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Widgets/IVInventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/IVInventoryComponent.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

void UIVInventorySlotWidget::SetAmount(const uint8 NewAmount)
{
	Amount = NewAmount;
}

void UIVInventorySlotWidget::SetItem(UIVBaseItemDA* NewItem)
{
	Item = NewItem;
}

void UIVInventorySlotWidget::CleanSlot()
{
	if (InventoryReference->IsSlotEmpty(SlotIndex))
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);

		SlotButton->SetToolTip(nullptr);
		SlotButton->SetIsEnabled(false);

        SetSlotFrameByRarity();
        Item = nullptr;
        Amount = 0;        
	}
}

void UIVInventorySlotWidget::UpdateSlot()
{
	if (!IsValid(InventoryReference))
		return;
    
	if (!Item)
		return;

	ItemIcon->SetBrushFromTexture(Item->Thumbnail.Get());
	ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

	Amount = InventoryReference->GetAmountAtIndex(SlotIndex);

	SlotButton->SetIsEnabled(true);

    SetSlotFrameByRarity();
	CreateDetailWidget();
}

void UIVInventorySlotWidget::SetInventoryReference(UIVInventoryComponent* TargetInventory)
{
	InventoryReference = TargetInventory;
}

void UIVInventorySlotWidget::SetWidgetProperties(UIVBaseItemDA* NewItem, const uint8 NewAmount,
                                                 const uint8 NewSlotIndex)
{
	Item = NewItem;
	Amount = NewAmount;
	SlotIndex = NewSlotIndex;
}