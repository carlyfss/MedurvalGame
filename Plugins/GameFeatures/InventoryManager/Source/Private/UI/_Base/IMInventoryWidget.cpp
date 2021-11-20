// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/_Base/IMInventoryWidget.h"

#include "IMInventorySlotWidget.h"
#include "Components/IMInventoryComponent.h"

void UIMInventoryWidget::SetInventoryReference(UIMInventoryComponent* InventoryRef)
{
	InventoryReference = InventoryRef;
}

void UIMInventoryWidget::SetSlotsPerRow(uint8 Slots)
{
	SlotsPerRow = Slots;
}

FVector2D UIMInventoryWidget::CalculateActionMenuLocation(const int32 Row, const int32 Column, const float ScrollOffset) const
{
	const int32 RowSize = Row * 70;
	const int32 ColumnSize = Column * 70;

	const float ScrollValue = RowSize - (ScrollOffset / 1.5f);
	const float ClampedScrollValue = FMath::Clamp(ScrollValue, 0.0f, 200.0f);

	return FVector2D(ColumnSize, ClampedScrollValue);
}
