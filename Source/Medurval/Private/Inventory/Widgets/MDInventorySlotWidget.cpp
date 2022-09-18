// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Inventory/Components/MDInventoryComponent.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

void UMDInventorySlotWidget::SetAmount(const uint8 NewAmount)
{
	Amount = NewAmount;
}

void UMDInventorySlotWidget::SetItem(UMDItemDataAsset* NewItem)
{
	Item = NewItem;
}

void UMDInventorySlotWidget::CleanSlot()
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

void UMDInventorySlotWidget::UpdateSlot()
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

void UMDInventorySlotWidget::SetInventoryReference(UMDInventoryComponent* TargetInventory)
{
	InventoryReference = TargetInventory;
}

void UMDInventorySlotWidget::SetWidgetProperties(UMDItemDataAsset* NewItem, const uint8 NewAmount,
                                                 const uint8 NewSlotIndex)
{
	Item = NewItem;
	Amount = NewAmount;
	SlotIndex = NewSlotIndex;
}
