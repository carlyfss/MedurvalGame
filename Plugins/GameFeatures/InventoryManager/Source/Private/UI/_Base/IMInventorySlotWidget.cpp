// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMInventorySlotWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/IMInventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

uint8 UIMInventorySlotWidget::GetAmount() const
{
	return Amount;
}

int32 UIMInventorySlotWidget::GetSlotIndex() const
{
	return SlotIndex;
}

void UIMInventorySlotWidget::SetSlotIndex(int32 Index)
{
	SlotIndex = Index;
}

UBaseItemPrimaryDA* UIMInventorySlotWidget::GetItemDataAtSlot() const
{
	return ItemAtSlot;
}

void UIMInventorySlotWidget::UpdateSlot()
{
	if (InventoryReference)
	{
		if (InventoryReference->IsSlotEmpty(SlotIndex))
		{
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
				
			SlotButton->SetIsEnabled(false);
			SlotButton->bIsEnabled = false;

			if (!ItemAtSlot.IsNull())
			{
				if (!ItemAtSlot->Thumbnail.IsNull())
				{
					UKismetSystemLibrary::UnloadPrimaryAsset(ItemAtSlot->Thumbnail->GetPrimaryAssetId());
				}

				UKismetSystemLibrary::UnloadPrimaryAsset(ItemAtSlot->GetPrimaryAssetId());

				ItemAtSlot = nullptr;
				
				SlotButton->SetIsEnabled(false);
				SlotButton->bIsEnabled = false;
			}
		}

		bool bIsSlotEmpty = false;
		uint8 AmountAtSlot = 0;

		ItemData = InventoryReference->GetItemInfoAtIndex(SlotIndex, bIsSlotEmpty, AmountAtSlot);

		if (ItemAtSlot == nullptr)
		{
			ItemAtSlot = Cast<UBaseItemPrimaryDA>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData));

			if (ItemAtSlot != nullptr)
			{
				UTexture2D* ItemIconAtSlot = Cast<UTexture2D>(UKismetSystemLibrary::LoadAsset_Blocking(ItemAtSlot->Thumbnail));

				if (ItemIconAtSlot)
				{
					ItemIcon->SetBrushFromTexture(ItemIconAtSlot);
					ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

					SlotButton->SetIsEnabled(true);
					SlotButton->bIsEnabled = true;
				}
			}

			SlotButton->SetIsEnabled(true);
			SlotButton->bIsEnabled = true;
		}

		Amount = AmountAtSlot;
	}
}

void UIMInventorySlotWidget::SetInventoryReference(UIMInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

UIMInventoryComponent* UIMInventorySlotWidget::GetInventoryReference() const
{
	return InventoryReference;
}
