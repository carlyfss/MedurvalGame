// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "MDInventoryWidget.generated.h"

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
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventorySlotWidget*> SlotWidgets;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventorySlotWidget*> EquipmentSlotWidgets;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventorySlotWidget*> AccessorySlotWidgets;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventorySlotWidget*> WeaponSlotWidgets;

protected:
	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetInventoryReference(UMDInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetupSlot(UMDInventorySlotWidget* SlotWidget, FMDInventorySlot SlotInfo, int32 SlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventoryWidget")
	UMDInventorySlotWidget* CreateInventorySlotWidget();

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

	virtual void NativeConstruct() override;
};
