// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMInventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/IMInventoryComponent.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

uint8 UIMInventorySlotWidget::GetAmount() const
{
	return Amount;
}

void UIMInventorySlotWidget::SetAmount(const uint8 NewAmount)
{
	this->Amount = NewAmount;
}

TSoftObjectPtr<UIMBaseItemDA> UIMInventorySlotWidget::GetItemData() const
{
	return this->ItemData;
}

void UIMInventorySlotWidget::SetItemData(const TSoftObjectPtr<UIMBaseItemDA> NewItemData)
{
	this->ItemData = NewItemData;
}

int32 UIMInventorySlotWidget::GetSlotIndex() const
{
	return SlotIndex;
}

void UIMInventorySlotWidget::SetSlotIndex(const int32 Index)
{
	SlotIndex = Index;
}

UIMBaseItemDA* UIMInventorySlotWidget::GetItemAtSlot() const
{
	return ItemAtSlot;
}

void UIMInventorySlotWidget::CleanSlot()
{
	if (InventoryReference->IsSlotEmpty(SlotIndex))
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);

		SlotButton->SetIsEnabled(false);

		if (!ItemAtSlot.IsNull())
		{
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			ItemAtSlot = nullptr;
			ItemData = nullptr;
			Amount = 0;
		}
	}
}

void UIMInventorySlotWidget::LoadSlotData()
{
	bool bIsSlotEmpty = false;
	uint8 AmountAtSlot = 0;

	ItemData = InventoryReference->GetItemInfoAtIndex(SlotIndex, bIsSlotEmpty, AmountAtSlot);

	if (IsValid(InventoryReference) && !bIsSlotEmpty)
	{
		if (!ItemData) { return; }

		if (!PlayerGameInstance) { return; }

		if (ItemAtSlot)
		{
			UpdateSlot();
			return;
		}

		const FSoftObjectPath ItemDataPath = ItemData.ToSoftObjectPath();
		const FSoftObjectPath ThumbnailSoftPath = ItemData->Thumbnail.ToSoftObjectPath();

		AssetsSoftPaths.AddUnique(ItemDataPath);
		AssetsSoftPaths.AddUnique(ThumbnailSoftPath);

		PlayerGameInstance->AssetLoader.RequestAsyncLoad(AssetsSoftPaths,
		                                                 FStreamableDelegate::CreateUObject(
			                                                 this, &UIMInventorySlotWidget::SetObjectsAfterLoad));
	}
}

void UIMInventorySlotWidget::UnloadSlotData()
{
	ItemAtSlot->UnloadItemAssets();

	CleanSlot();

	for (FSoftObjectPath AssetsSoftPath : AssetsSoftPaths)
	{
		PlayerGameInstance->AssetLoader.Unload(AssetsSoftPath);
	}
}

void UIMInventorySlotWidget::SetObjectsAfterLoad()
{
	ItemAtSlot = ItemData.Get();
	ItemAtSlot->SetLoadedItemAssets(InventoryReference->GetOwner());

	UpdateSlot();
}

void UIMInventorySlotWidget::UpdateSlot()
{
	if (IsValid(InventoryReference))
	{
		if (ItemAtSlot)
		{
			UTexture2D* Thumbnail = ItemAtSlot->GetItemThumbnail();

			if (Thumbnail)
			{
				ItemIcon->SetBrushFromTexture(Thumbnail);
				ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

				Amount = InventoryReference->GetAmountAtIndex(SlotIndex);

				SlotButton->SetIsEnabled(true);
			}
		}
	}
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

void UIMInventorySlotWidget::SetPlayerGameInstance(UMDGameInstance* TargetGameInstance)
{
	PlayerGameInstance = TargetGameInstance;
}

UMDGameInstance* UIMInventorySlotWidget::GetPlayerGameInstance() const
{
	return PlayerGameInstance;
}
