// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Components/Image.h"
#include "Core/Widgets/MDButtonWidget.h"
#include "Inventory/Components/MDInventoryComponent.h"
#include "Engine/StreamableManager.h"
#include "CommonNumericTextBlock.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMDInventorySlotWidget::CleanSlot()
{
	Icon->SetVisibility(ESlateVisibility::Collapsed);
	Icon->SetBrushFromLazyTexture(nullptr);
	SlotAmount->SetVisibility(ESlateVisibility::Collapsed);

	SlotButton->SetToolTip(nullptr);
	SlotButton->SetIsEnabled(false);

	SetSlotFrameByRarity();

	SlotInfo.ClearSlot();
}

void UMDInventorySlotWidget::SetSlotInfo(FMDInventorySlot NewSlotInfo, int32 NewIndex)
{
	SlotInfo.Item = NewSlotInfo.Item;
	SlotInfo.Amount = NewSlotInfo.Amount;
	SlotIndex = NewIndex;
	Item = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(SlotInfo.Item);

	UpdateSlot();
}

void UMDInventorySlotWidget::UpdateSlot()
{
	if (IsValid(InventoryReference) && SlotInfo.IsValid())
	{
		Icon->SetBrushFromLazyTexture(Item->Thumbnail);
		Icon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		if (SlotInfo.Amount <= 1)
		{
			SlotAmount->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			SlotAmount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		SlotAmount->SetCurrentValue(SlotInfo.Amount);
		SlotButton->SetIsEnabled(true);

		SetSlotFrameByRarity();
		CreateDetailWidget();
	}
}

void UMDInventorySlotWidget::SetInventoryReference(UMDInventoryComponent* TargetInventory)
{
	InventoryReference = TargetInventory;
}
