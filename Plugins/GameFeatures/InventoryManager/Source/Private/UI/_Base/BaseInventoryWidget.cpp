// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/BaseInventoryWidget.h"

#include "BaseInventorySlotWidget.h"
#include "Components/InventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UBaseInventoryWidget::GenerateSlotWidgets()
{
	if (SlotPanel)
	{
		SlotPanel->ClearChildren();
		SlotsWidgets.Reset();

		if (IsValid(InventoryReference))
		{
			FScopeLock Lock(&SocketsCriticalSection);
			
			TArray<FInventorySlot> Slots = InventoryReference->GetInventorySlots();
			
			for (int i = 0; i < Slots.Num(); i++)
			{
				UBaseInventorySlotWidget* SlotWidget = Cast<UBaseInventorySlotWidget>(CreateWidget(GetWorld(), UBaseInventorySlotWidget::StaticClass()));

				if (SlotWidget != nullptr)
				{
					SlotWidget->SetInventoryReference(InventoryReference);
					SlotWidget->SetSlotIndex(i);

					SlotsWidgets.Add(SlotWidget);

					UUniformGridSlot* GridSlot = SlotPanel->AddChildToUniformGrid(SlotWidget);

					if (IsValid(GridSlot))
					{
						uint8 SlotRow;
						uint8 SlotColumn;

						SetSlotColumnAndRow(i, SlotColumn, SlotRow);

						GridSlot->SetRow(SlotRow);
						GridSlot->SetColumn(SlotColumn);
					}
				}
			}
		}
	}
	
}

void UBaseInventoryWidget::SetInventoryReference(UInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UBaseInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}

void UBaseInventoryWidget::SetSlotColumnAndRow(int32 Index, uint8& Column, uint8& Row) const
{
	const uint8 SlotRow = static_cast<uint8>(FMath::TruncToInt(Index / SlotsPerRow));
	
	const uint8 ColumnTruncateValue = FMath::TruncToInt(Index / SlotsPerRow);
	const uint8 ColumnRemainderValue = (Index / SlotsPerRow) - ColumnTruncateValue;
	const uint8 SlotColumn = static_cast<uint8>(FMath::TruncToInt(ColumnRemainderValue));

	Column = SlotColumn;
	Row = SlotRow;
}
