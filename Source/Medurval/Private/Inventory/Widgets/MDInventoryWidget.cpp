// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Widgets/MDInventoryWidget.h"

#include "Components/GridPanel.h"
#include "Components/UniformGridPanel.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Components/MDInventoryComponent.h"
#include "Inventory/Widgets/MDInventoryAccessorySlotWidget.h"
#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Inventory/Widgets/MDInventoryWeaponSlotWidget.h"
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
		if (SlotWidget)
		{
			SetupSlot(SlotWidget, Slots[i], i);

			int32 Row;
			int32 Column;
			CalculateSlotRowAndColumn(i, Row, Column);

			SlotPanel->AddChildToUniformGrid(SlotWidget, Row, Column);

			SlotWidget->CleanSlot();
			SlotWidget->SetSlotInfo(Slots[i], i);
			SlotWidget->UpdateSlot();
		}
	}
}

void UMDInventoryWidget::GenerateEquipmentSlotWidgets()
{
	EquipmentSlotWidgets.Empty();

	TArray<FMDInventoryEquipmentSlot> EquipmentSlots = InventoryReference->GetEquipmentSlots();
	for (int i = 0; i < EquipmentSlots.Num(); i++)
	{
		UMDInventoryEquipmentSlotWidget* SlotWidget = CreateInventoryEquipmentSlotWidget();
		if (SlotWidget)
		{
			SetupEquipmentSlot(SlotWidget, EquipmentSlots[i]);

			SlotWidget->SetPadding(FMargin(5, 5));

			EquipmentSlotGrid->AddChildToGrid(SlotWidget, i, 0);

			SlotWidget->CleanSlot();
			SlotWidget->SetSlotInfo(EquipmentSlots[i]);
			SlotWidget->SetSlotAttachment(EquipmentSlots[i].Attachment);
			SlotWidget->UpdateSlot();
		}
	}
}

void UMDInventoryWidget::GenerateAccessorySlotWidgets()
{
	AccessorySlotWidgets.Empty();

	const int32 AccessorySlotColumn = InventoryReference->GetWeaponSlotsAmount() + 1;

	TArray<FMDInventoryAccessorySlot> AccessorySlots = InventoryReference->GetAccessorySlots();
	for (int i = 0; i < AccessorySlots.Num(); i++)
	{
		UMDInventoryAccessorySlotWidget* SlotWidget =
			CreateInventoryAccessorySlotWidget();
		if (SlotWidget)
		{
			SetupAccessorySlot(SlotWidget, AccessorySlots[i]);

			SlotWidget->SetPadding(FMargin(5, 5));

			EquipmentSlotGrid->AddChildToGrid(SlotWidget, i,
			                                  AccessorySlotColumn);

			SlotWidget->CleanSlot();
			SlotWidget->SetSlotInfo(AccessorySlots[i]);
			SlotWidget->UpdateSlot();
		}
	}
}

void UMDInventoryWidget::GenerateWeaponSlotWidgets()
{
	WeaponSlotWidgets.Empty();

	const int32 WeaponSlotRow = InventoryReference->GetEquipmentSlotsAmount();

	TArray<FMDInventoryWeaponSlot> WeaponSlots = InventoryReference->GetWeaponSlots();
	for (int i = 0; i < WeaponSlots.Num(); i++)
	{
		UMDInventoryWeaponSlotWidget* SlotWidget = CreateInventoryWeaponSlotWidget();
		SetupWeaponSlot(SlotWidget, WeaponSlots[i]);

		SlotWidget->SetPadding(FMargin(10, 5));

		// Add 1 offset in column to skip the first column in the grid
		EquipmentSlotGrid->AddChildToGrid(SlotWidget, WeaponSlotRow, i + 1);

		SlotWidget->CleanSlot();
		SlotWidget->SetSlotInfo(WeaponSlots[i]);
		SlotWidget->UpdateSlot();
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
		InventoryReference->OnEquipmentItemEquipped.RemoveAll(this);
		InventoryReference->OnEquipmentItemUnequipped.RemoveAll(this);

		InventoryReference->OnItemRemoved.AddDynamic(this, &UMDInventoryWidget::OnItemRemoved);
		InventoryReference->OnUpdateSlotAtIndex.AddDynamic(this, &UMDInventoryWidget::UpdateSlotAtIndex);
		InventoryReference->OnEquipmentItemEquipped.AddDynamic(this, &UMDInventoryWidget::UpdateEquipmentSlots);
		InventoryReference->OnEquipmentItemUnequipped.AddDynamic(
			this, &UMDInventoryWidget::UpdateEquipmentSlotAtAttachment);
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

void UMDInventoryWidget::SetupEquipmentSlot(UMDInventoryEquipmentSlotWidget* SlotWidget,
                                            FMDInventoryEquipmentSlot SlotInfo)
{
	SlotWidget->SetInventoryReference(InventoryReference);
	SlotWidget->SetSlotInfo(SlotInfo);

	EquipmentSlotWidgets.Add(SlotWidget);
	SlotWidget->UpdateSlot();
}

void UMDInventoryWidget::SetupAccessorySlot(
	UMDInventoryAccessorySlotWidget* SlotWidget,
	FMDInventoryAccessorySlot SlotInfo)
{
	SlotWidget->SetInventoryReference(InventoryReference);
	SlotWidget->SetSlotInfo(SlotInfo);

	AccessorySlotWidgets.Add(SlotWidget);
	SlotWidget->UpdateSlot();
}

void UMDInventoryWidget::SetupWeaponSlot(UMDInventoryWeaponSlotWidget* SlotWidget, FMDInventoryWeaponSlot SlotInfo)
{
	SlotWidget->SetInventoryReference(InventoryReference);
	SlotWidget->SetSlotInfo(SlotInfo);

	WeaponSlotWidgets.Add(SlotWidget);
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

void UMDInventoryWidget::UpdateEquipmentSlots(FPrimaryAssetId Item, EMDEquipmentAttachment Attachment)
{
	TArray<FMDInventoryEquipmentSlot> EquipmentSlots = InventoryReference->GetEquipmentSlots();

	for (int i = 0; i < EquipmentSlotWidgets.Num(); i++)
	{
		UMDInventoryEquipmentSlotWidget* SlotWidget = EquipmentSlotWidgets[i];

		if (!EquipmentSlots[i].IsValid())
		{
			SlotWidget->SetSlotInfo(FMDInventoryEquipmentSlot());
			SlotWidget->CleanSlot();
		}
		else
		{
			SlotWidget->SetSlotInfo(EquipmentSlots[i]);
			SlotWidget->UpdateSlot();
		}
	}
}

void UMDInventoryWidget::UpdateEquipmentSlotAtAttachment(EMDEquipmentAttachment Attachment)
{
	bool bHasFound;
	TArray<FMDInventoryEquipmentSlot> EquipmentSlots = InventoryReference->GetEquipmentSlots();
	int32 SlotIndex = InventoryReference->FindSlotIndexByAttachment(Attachment, bHasFound);

	UMDInventoryEquipmentSlotWidget* SlotWidget = EquipmentSlotWidgets[SlotIndex];

	if (EquipmentSlots[SlotIndex].IsEmpty())
	{
		SlotWidget->SetSlotInfo(FMDInventoryEquipmentSlot());
		SlotWidget->CleanSlot();
	}
	else
	{
		SlotWidget->SetSlotInfo(EquipmentSlots[SlotIndex]);
		SlotWidget->UpdateSlot();
	}
}

void UMDInventoryWidget::UpdateAccessorySlotAtAttachment(EMDAccessoryAttachment Attachment)
{
	bool bHasFound;
	TArray<FMDInventoryAccessorySlot> AccessorySlots = InventoryReference->GetAccessorySlots();
	int32 SlotIndex = InventoryReference->FindSlotIndexByAttachment(Attachment, bHasFound);

	UMDInventoryAccessorySlotWidget* SlotWidget = AccessorySlotWidgets[SlotIndex];

	if (AccessorySlots[SlotIndex].IsEmpty())
	{
		SlotWidget->SetSlotInfo(FMDInventoryAccessorySlot());
		SlotWidget->CleanSlot();
	}
	else
	{
		SlotWidget->SetSlotInfo(AccessorySlots[SlotIndex]);
		SlotWidget->UpdateSlot();
	}
}

void UMDInventoryWidget::UpdateWeaponSlotAtAttachment(EMDWeaponAttachment Attachment)
{
	bool bHasFound;
	TArray<FMDInventoryWeaponSlot> WeaponSlots = InventoryReference->GetWeaponSlots();
	int32 SlotIndex = InventoryReference->FindSlotIndexByAttachment(Attachment, bHasFound);

	UMDInventoryWeaponSlotWidget* SlotWidget = WeaponSlotWidgets[SlotIndex];

	if (WeaponSlots[SlotIndex].IsEmpty())
	{
		SlotWidget->SetSlotInfo(FMDInventoryWeaponSlot());
		SlotWidget->CleanSlot();
	}
	else
	{
		SlotWidget->SetSlotInfo(WeaponSlots[SlotIndex]);
		SlotWidget->UpdateSlot();
	}
}

void UMDInventoryWidget::UpdateAccessorySlots(FPrimaryAssetId Item, EMDAccessoryAttachment Attachment)
{
	TArray<FMDInventoryAccessorySlot> AccessorySlots = InventoryReference->GetAccessorySlots();

	for (int i = 0; i < AccessorySlotWidgets.Num(); i++)
	{
		UMDInventoryAccessorySlotWidget* SlotWidget = AccessorySlotWidgets[i];

		if (!AccessorySlots[i].IsValid())
		{
			SlotWidget->SetSlotInfo(FMDInventoryAccessorySlot());
			SlotWidget->CleanSlot();
		}
		else
		{
			SlotWidget->SetSlotInfo(AccessorySlots[i]);
			SlotWidget->UpdateSlot();
		}
	}
}

void UMDInventoryWidget::UpdateWeaponSlots(FPrimaryAssetId Item, EMDWeaponAttachment Attachment)
{
	TArray<FMDInventoryWeaponSlot> WeaponSlots = InventoryReference->GetWeaponSlots();

	for (int i = 0; i < WeaponSlotWidgets.Num(); i++)
	{
		UMDInventoryWeaponSlotWidget* SlotWidget = WeaponSlotWidgets[i];

		if (!WeaponSlots[i].IsValid())
		{
			SlotWidget->SetSlotInfo(FMDInventoryWeaponSlot());
			SlotWidget->CleanSlot();
		}
		else
		{
			SlotWidget->SetSlotInfo(WeaponSlots[i]);
			SlotWidget->UpdateSlot();
		}
	}
}

void UMDInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotWidgetClass)
	{
		GetMDGameInstance()->LoadClass(SlotWidgetClass);
	}

	if (EquipmentSlotWidgetClass)
	{
		GetMDGameInstance()->LoadClass(EquipmentSlotWidgetClass);
	}
}
