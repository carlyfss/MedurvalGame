// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "UI/_Base/IMInventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/IMInventoryComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

uint8 UIMInventorySlotWidget::GetAmount() const
{
	return Amount;
}

void UIMInventorySlotWidget::SetAmount(const uint8 NewAmount)
{
	Amount = NewAmount;
}

UIMBaseItemDA *UIMInventorySlotWidget::GetItem() const
{
	return Item;
}

void UIMInventorySlotWidget::SetItem(UIMBaseItemDA *NewItem)
{
	Item = NewItem;
}

void UIMInventorySlotWidget::CleanSlot()
{
	if (InventoryReference->IsSlotEmpty(SlotIndex))
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);

		SlotButton->SetToolTip(nullptr);
		SlotButton->SetIsEnabled(false);

		if (!Item)
		{
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			Amount = 0;
		}
	}
}

void UIMInventorySlotWidget::UpdateSlot()
{
	if (!IsValid(InventoryReference))
		return;
	if (!Item)
		return;

	ItemIcon->SetBrushFromTexture(Item->Thumbnail.Get());
	ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

	Amount = InventoryReference->GetAmountAtIndex(SlotIndex);

	SlotButton->SetIsEnabled(true);

	CreateDetailWidget();
}

void UIMInventorySlotWidget::SetInventoryReference(UIMInventoryComponent *TargetInventory)
{
	InventoryReference = TargetInventory;
}

void UIMInventorySlotWidget::SetWidgetProperties(UIMBaseItemDA *NewItem, const uint8 NewAmount, const uint8 NewSlotIndex)
{
	Item = NewItem;
	Amount = NewAmount;
	SlotIndex = NewSlotIndex;
}

UButton *UIMInventorySlotWidget::GetSlotButton() const
{
	return SlotButton;
}

UIMInventoryComponent *UIMInventorySlotWidget::GetInventoryReference() const
{
	return InventoryReference;
}

uint8 UIMInventorySlotWidget::GetSlotIndex() const
{
	return SlotIndex;
}