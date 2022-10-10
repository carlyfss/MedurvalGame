// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryWidget.h"

#include "Components/GridPanel.h"
#include "Components/UniformGridPanel.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Inventory/Components/MDInventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMDInventoryWidget::CalculateSlotRowAndColumn(int32 Index, int32& Row, int32& Column) const
{
	Row = UKismetMathLibrary::FTrunc(Index / SlotsPerRow);
	Column = UKismetMathLibrary::FTrunc(Index % SlotsPerRow);
}

void UMDInventoryWidget::OnItemRemoved(FPrimaryAssetId ItemRemoved, int32 Amount, int32 Index)
{
	SlotWidgets[Index]->CleanSlot();
}

TArray<UMDInventorySlotWidget*> UMDInventoryWidget::GetSlotWidgets()
{
	return SlotWidgets;
}

void UMDInventoryWidget::GenerateSlotWidgets()
{
	SetSlotsPerRow(InventoryReference->GetSlotsPerRow());
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
		SlotWidget->SetSlotInfo(Slots[i], i);
	}
}

void UMDInventoryWidget::GenerateEquipmentSlotWidgets()
{
	EquipmentSlotWidgets.Empty();

	TArray<FMDInventoryEquipmentSlot> EquipmentSlots = InventoryReference->GetEquipmentSlots();
	for (int i = 0; i < EquipmentSlots.Num(); i++)
	{
		UMDInventorySlotWidget* SlotWidget = CreateInventorySlotWidget();
		SetupSlot(SlotWidget, EquipmentSlots[i], i);

		SlotWidget->SetPadding(FMargin(5, 5));

		EquipmentSlotGrid->AddChildToGrid(SlotWidget, i, 0);

		SlotWidget->CleanSlot();
		SlotWidget->SetSlotInfo(EquipmentSlots[i], i);
	}
}

void UMDInventoryWidget::GenerateAccessorySlotWidgets()
{
	AccessorySlotWidgets.Empty();

	const int32 AccessorySlotColumn = InventoryReference->GetWeaponSlotsAmount() + 1;

	TArray<FMDInventoryAccessorySlot> AccessorySlots = InventoryReference->GetAccessorySlots();
	for (int i = 0; i < AccessorySlots.Num(); i++)
	{
		UMDInventorySlotWidget* SlotWidget = CreateInventorySlotWidget();
		SetupSlot(SlotWidget, AccessorySlots[i], i);

		SlotWidget->SetPadding(FMargin(5, 5));

		EquipmentSlotGrid->AddChildToGrid(SlotWidget, i, AccessorySlotColumn);

		SlotWidget->CleanSlot();
		SlotWidget->SetSlotInfo(AccessorySlots[i], i);
	}
}

void UMDInventoryWidget::GenerateWeaponSlotWidgets()
{
	WeaponSlotWidgets.Empty();

	const int32 WeaponSlotRow = InventoryReference->GetEquipmentSlotsAmount() + 1;

	TArray<FMDInventoryWeaponSlot> WeaponSlots = InventoryReference->GetWeaponSlots();
	for (int i = 0; i < WeaponSlots.Num(); i++)
	{
		UMDInventorySlotWidget* SlotWidget = CreateInventorySlotWidget();
		SetupSlot(SlotWidget, WeaponSlots[i], i);

		SlotWidget->SetPadding(FMargin(10, 5));

		// Add 1 offset in column to skip the first column in the grid
		EquipmentSlotGrid->AddChildToGrid(SlotWidget, WeaponSlotRow, i + 1);

		SlotWidget->CleanSlot();
		SlotWidget->SetSlotInfo(WeaponSlots[i], i);
	}
}

void UMDInventoryWidget::GenerateAllSlotWidgets()
{
	if (InventoryReference)
	{
		SlotPanel->ClearChildren();
		EquipmentSlotGrid->ClearChildren();

		GenerateSlotWidgets();
		GenerateEquipmentSlotWidgets();
		GenerateAccessorySlotWidgets();
		GenerateWeaponSlotWidgets();

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

void UMDInventoryWidget::SetupSlot(UMDInventorySlotWidget* SlotWidget, FMDInventorySlot SlotInfo, int32 SlotIndex)
{
	SlotWidget->SetInventoryReference(InventoryReference);
	SlotWidget->SetSlotInfo(SlotInfo, SlotIndex);

	SlotWidgets.Add(SlotWidget);
	SlotWidget->UpdateSlot();
}

void UMDInventoryWidget::UpdateSlotAtIndex(int32 SlotIndex)
{
	UMDInventorySlotWidget* SlotWidget = GetSlotWidgets()[SlotIndex];
	FMDInventorySlot TargetSlot = InventoryReference->GetSlots()[SlotIndex];

	if (InventoryReference->IsSlotEmpty(SlotIndex))
	{
		SlotWidget->CleanSlot();
	}
	else
	{
		SlotWidget->SetSlotInfo(TargetSlot, SlotIndex);
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
