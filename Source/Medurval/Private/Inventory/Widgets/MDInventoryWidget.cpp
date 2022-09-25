// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryWidget.h"

#include "Components/UniformGridPanel.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Inventory/Components/MDInventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMDInventoryWidget::CalculateSlotRowAndColumn(int32 Index, int32& Row, int32& Column)
{
	Row = UKismetMathLibrary::FTrunc(Index / SlotsPerRow);
	Column = UKismetMathLibrary::FTrunc(Index % SlotsPerRow);
}

void UMDInventoryWidget::OnItemRemoved(UMDItemDataAsset* ItemRemoved, uint8 Amount, uint8 Index)
{
	SlotWidgets[Index]->CleanSlot();
}

TArray<UMDInventorySlotWidget*> UMDInventoryWidget::GetSlotWidgets()
{
	return SlotWidgets;
}

void UMDInventoryWidget::GenerateSlotWidgets()
{
	if (InventoryReference)
	{
		SetSlotsPerRow(InventoryReference->GetSlotsPerRow());

		SlotPanel->ClearChildren();
		SlotWidgets.Empty();

		TArray<FMDInventorySlot> Slots = InventoryReference->GetSlots();

		for (int i = 0; i < Slots.Num(); i++)
		{
			UMDInventorySlotWidget* SlotWidget = CreateInventorySlotWidget();
			SetupSlot(SlotWidget, Slots[i], i);

			int32 Row;
			int32 Column;
			CalculateSlotRowAndColumn(i, Row, Column);

			SlotPanel->AddChildToUniformGrid(SlotWidget, Row, Column);

			SlotWidget->CleanSlot();
		}

		InventoryReference->OnItemRemoved.RemoveAll(this);
		InventoryReference->OnUpdateSlotAtIndex.RemoveAll(this);

		InventoryReference->OnItemRemoved.AddDynamic(this, &UMDInventoryWidget::OnItemRemoved);
		InventoryReference->OnUpdateSlotAtIndex.AddDynamic(this, &UMDInventoryWidget::UpdateSlotAtIndex);
	}
}

void UMDInventoryWidget::SetInventoryReference(UMDInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UMDInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}

void UMDInventoryWidget::SetupSlot(UMDInventorySlotWidget* SlotWidget, FMDInventorySlot SlotInfo, int32 Index)
{
	SlotWidget->SetInventoryReference(InventoryReference);
	SlotWidget->SetWidgetProperties(SlotInfo.Item, SlotInfo.Amount, Index);

	SlotWidgets.Add(SlotWidget);
	SlotWidget->UpdateSlot();
}

void UMDInventoryWidget::UpdateSlotAtIndex(uint8 SlotIndex)
{
	UMDInventorySlotWidget* SlotWidget = GetSlotWidgets()[SlotIndex];
	FMDInventorySlot TargetSlot = InventoryReference->GetSlots()[SlotIndex];

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

void UMDInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotWidgetClass)
	{
		GetMDGameInstance()->LoadClass(SlotWidgetClass);
	}
}
