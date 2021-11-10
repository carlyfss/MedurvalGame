// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/BaseInventorySlotWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

uint8 UBaseInventorySlotWidget::GetAmount() const
{
	return Amount;
}

int32 UBaseInventorySlotWidget::GetSlotIndex() const
{
	return SlotIndex;
}

void UBaseInventorySlotWidget::SetSlotIndex(int32 Index)
{
	SlotIndex = Index;
}

UBaseItemDA* UBaseInventorySlotWidget::GetItemDataAtSlot() const
{
	return ItemAtSlot;
}

void UBaseInventorySlotWidget::UpdateSlot()
{
	if (InventoryReference)
	{
		if (InventoryReference->IsSlotEmpty(SlotIndex))
		{
			SlotButton->SetIsEnabled(false);
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			UKismetSystemLibrary::UnloadPrimaryAsset(ItemAtSlot->Thumbnail->GetPrimaryAssetId());
			UKismetSystemLibrary::UnloadPrimaryAsset(ItemAtSlot->GetPrimaryAssetId());
			ItemAtSlot = nullptr;
			ItemData.Reset();
		}

		SlotButton->SetIsEnabled(true);

		bool bIsSlotEmpty = false;
		constexpr uint8 AmountAtSlot = 0;

		ItemData = InventoryReference->GetItemInfoAtIndex(SlotIndex, bIsSlotEmpty, Amount);

		Amount = AmountAtSlot;

		ItemAtSlot = Cast<UBaseItemDA>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData));

		if (ItemAtSlot != nullptr)
		{
			UTexture2D* ItemIconAtSlot = Cast<UTexture2D>(UKismetSystemLibrary::LoadAsset_Blocking(ItemAtSlot->Thumbnail));

			if (ItemIconAtSlot)
			{
				ItemIcon->SetBrushFromTexture(ItemIconAtSlot);
				ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
		}
	}
}

void UBaseInventorySlotWidget::SetInventoryReference(UInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

UInventoryComponent* UBaseInventorySlotWidget::GetInventoryReference() const
{
	return InventoryReference;
}
