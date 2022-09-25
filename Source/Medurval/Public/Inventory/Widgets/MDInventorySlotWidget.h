// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "Inventory/Interfaces/MDInventoryInterface.h"
#include "MDInventorySlotWidget.generated.h"

class UCommonNumericTextBlock;
class UMDButtonWidget;
class UMDDetailWidget;
class UMDGameInstance;
class UMDItemDataAsset;
class UMDInventoryComponent;
class UTextBlock;
class UButton;
class UImage;

UCLASS(meta = (DisplayName = "InventorySlotWidget"))
class MEDURVAL_API UMDInventorySlotWidget final : public UMDActivatableWidget, public IMDInventoryInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDItemDataAsset> Item = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	uint8 Amount;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	uint8 SlotIndex;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDInventoryComponent> InventoryReference;

	// Widget Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UMDButtonWidget> SlotButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCommonNumericTextBlock> SlotAmount = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDDetailWidget> DetailWidget = nullptr;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "InventorySlot")
	void CreateDetailWidget();

public:
	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetInventoryReference(UMDInventoryComponent* TargetInventory);

	void SetAmount(const uint8 NewAmount);

	void SetItem(UMDItemDataAsset* NewItem);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventorySlot")
	void SetSlotFrameByRarity();
	
	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void CleanSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetWidgetProperties(UMDItemDataAsset* NewItem, const uint8 NewAmount, const uint8 NewSlotIndex);
};
