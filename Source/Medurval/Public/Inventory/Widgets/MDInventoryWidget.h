// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDInventoryEquipmentSlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "MDInventoryWidget.generated.h"

class UMDInventoryWeaponSlotWidget;
class UMDInventoryAccessorySlotWidget;
class UMDInventorySlotWidget;
class UMDInventoryComponent;
class UUniformGridPanel;
class UGridPanel;
/**
 *
 */
UCLASS(meta = (DisplayName = "InventoryWidget"))
class MEDURVAL_API UMDInventoryWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UUniformGridPanel> SlotPanel = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UGridPanel> EquipmentSlotGrid = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSoftClassPtr<UMDInventorySlotWidget> SlotWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSoftClassPtr<UMDInventoryEquipmentSlotWidget> EquipmentSlotWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSoftClassPtr<UMDInventoryAccessorySlotWidget> AccessorySlotWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSoftClassPtr<UMDInventoryWeaponSlotWidget> WeaponSlotWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventorySlotWidget*> SlotWidgets;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventoryEquipmentSlotWidget*> EquipmentSlotWidgets;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventoryAccessorySlotWidget*> AccessorySlotWidgets;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventoryWeaponSlotWidget*> WeaponSlotWidgets;

protected:
	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetInventoryReference(UMDInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetupSlot(UMDInventorySlotWidget* SlotWidget, FMDInventorySlot SlotInfo, int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetupEquipmentSlot(UMDInventoryEquipmentSlotWidget* SlotWidget, FMDInventoryEquipmentSlot SlotInfo);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetupAccessorySlot(UMDInventoryAccessorySlotWidget* SlotWidget, FMDInventoryAccessorySlot SlotInfo);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetupWeaponSlot(UMDInventoryWeaponSlotWidget* SlotWidget, FMDInventoryWeaponSlot SlotInfo);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventoryWidget")
	UMDInventorySlotWidget* CreateInventorySlotWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventoryWidget")
	UMDInventoryEquipmentSlotWidget* CreateInventoryEquipmentSlotWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventoryWidget")
	UMDInventoryAccessorySlotWidget* CreateInventoryAccessorySlotWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventoryWidget")
	UMDInventoryWeaponSlotWidget* CreateInventoryWeaponSlotWidget();

	void CalculateSlotRowAndColumn(int32 Index, int32& Row, int32& Column) const;

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void OnItemRemoved(FPrimaryAssetId ItemRemoved, int32 Amount, int32 Index);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void GenerateEquipmentSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void GenerateAccessorySlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void GenerateWeaponSlotWidgets();
	
public:
	TArray<UMDInventorySlotWidget*> GetSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void GenerateAllSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateSlotAtIndex(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateEquipmentSlots(FPrimaryAssetId Item, EMDEquipmentAttachment Attachment);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateAccessorySlots(FPrimaryAssetId Item, EMDAccessoryAttachment Attachment);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateWeaponSlots(FPrimaryAssetId Item, EMDWeaponAttachment Attachment);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateEquipmentSlotAtAttachment(EMDEquipmentAttachment Attachment);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateAccessorySlotAtAttachment(EMDAccessoryAttachment Attachment);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateWeaponSlotAtAttachment(EMDWeaponAttachment Attachment);

	virtual void NativeConstruct() override;
};
