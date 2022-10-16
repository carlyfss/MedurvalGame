// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "Inventory/Interfaces/MDInventoryInterface.h"
#include "CommonLazyImage.h"
#include "Inventory/Structs/MDInventoryAccessorySlot.h"
#include "Inventory/Structs/MDInventoryEquipmentSlot.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "Inventory/Structs/MDInventoryWeaponSlot.h"
#include "MDInventorySlotWidget.generated.h"

class UCommonNumericTextBlock;
class UMDButtonWidget;
class UMDDetailWidget;
class UMDGameInstance;
class UMDItemDataAsset;
class UMDInventoryComponent;
class UTextBlock;
class UButton;

UCLASS(meta = (DisplayName = "InventorySlotWidget"))
class MEDURVAL_API UMDInventorySlotWidget : public UMDActivatableWidget, public IMDInventoryInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDItemDataAsset> Item = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	FMDInventorySlot SlotInfo = FMDInventorySlot();

	UPROPERTY(BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDInventoryComponent> InventoryReference;

	UPROPERTY(BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	int32 SlotIndex = -1;

	// Widget Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UMDButtonWidget> SlotButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCommonNumericTextBlock> SlotAmount = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCommonLazyImage> Icon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDDetailWidget> DetailWidget = nullptr;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "InventorySlot")
	void CreateDetailWidget();

public:
	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetInventoryReference(UMDInventoryComponent* TargetInventory);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventorySlot")
	void SetSlotFrameByRarity();

	bool IsEmpty() const;
	
	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void CleanSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetSlotInfo(FMDInventorySlot NewSlotInfo, int32 NewIndex);
};
