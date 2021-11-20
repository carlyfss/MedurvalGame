// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMSlotActionMenuWidget.h"

#include "Components/Button.h"
#include "Components/IMInventoryComponent.h"
#include "Components/TextBlock.h"

void UIMSlotActionMenuWidget::Update(const int32 Index)
{
	CurrentIndex = Index;
	bool bIsSlotEmpty = false;
	uint8 AmountAtIndex = 0;

	ItemData = InventoryReference->GetItemInfoAtIndex(Index, bIsSlotEmpty, AmountAtIndex);
	Amount = AmountAtIndex;

	UBaseItemPrimaryDA* Item = ItemData.LoadSynchronous();

	if (Item != nullptr)
	{
		if (Item->bCanBeUsed)
		{
			UseItemText->SetText(ItemData->OnUseText);
			UseButton->SetVisibility(ESlateVisibility::Visible);
		} else
		{
			UseButton->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (Item->Category == EIMItemCategories::Quest)
		{
			DiscardButton->SetVisibility(ESlateVisibility::Collapsed);
		} else
		{
			DiscardButton->SetVisibility(ESlateVisibility::Visible);
		}

		if (Item->bCanBeStacked && Amount > 1)
		{
			SplitButton->SetVisibility(ESlateVisibility::Visible);
		} else
		{
			SplitButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}