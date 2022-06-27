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
	this->Amount = NewAmount;
}

UIMBaseItemDA* UIMInventorySlotWidget::GetItem() const
{
	return this->Item;
}

void UIMInventorySlotWidget::SetItem(UIMBaseItemDA* NewItem)
{
	this->Item = NewItem;
}

int32 UIMInventorySlotWidget::GetSlotIndex() const
{
	return SlotIndex;
}

void UIMInventorySlotWidget::SetSlotIndex(const int32 Index)
{
	SlotIndex = Index;
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
	if (!IsValid(InventoryReference)) return;
	if (!Item) return;

	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());
	if (!AssetManager) return;

	UTexture2D* Thumbnail = Cast<UTexture2D>(Item->Thumbnail.Get());

	if (!Thumbnail) return;

	ItemIcon->SetBrushFromTexture(Thumbnail);
	ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

	Amount = InventoryReference->GetAmountAtIndex(SlotIndex);

	SlotButton->SetIsEnabled(true);

	CreateDetailWidget();
}

void UIMInventorySlotWidget::SetInventoryReference(UIMInventoryComponent* TargetInventory)
{
	InventoryReference = TargetInventory;
}

UButton* UIMInventorySlotWidget::GetSlotButton() const
{
	return SlotButton;
}

UIMInventoryComponent* UIMInventorySlotWidget::GetInventoryReference() const
{
	return InventoryReference;
}
