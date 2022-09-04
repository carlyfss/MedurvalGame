// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IVInventoryInterface.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "IVInventorySlotWidget.generated.h"

class UIVDetailWidget;
class UMDGameInstance;
class UIVBaseItemDA;
class UIVInventoryComponent;
class UTextBlock;
class UButton;
class UImage;

UCLASS(meta = (DisplayName = "InventorySlotWidget"))
class INVENTORY_API UIVInventorySlotWidget final : public UCBCommonActivatableWidget, public IIVInventoryInterface
{
	GENERATED_BODY()

    UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UIVBaseItemDA> Item = nullptr;

    UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	uint8 Amount;

    UPROPERTY(Transient, BlueprintReadOnly, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	uint8 SlotIndex;

    UPROPERTY(Transient, BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UIVInventoryComponent> InventoryReference;

	// Widget Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> SlotButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
			  meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
			  meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> AmountText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot", meta = (AllowPrivateAccess = true))
	TObjectPtr<UIVDetailWidget> DetailWidget = nullptr;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "InventorySlot")
	void CreateDetailWidget();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetInventoryReference(UIVInventoryComponent *TargetInventory);

	void SetAmount(const uint8 NewAmount);

	void SetItem(UIVBaseItemDA *NewItem);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "InventorySlot")
    void SetSlotFrameByRarity();

public:
	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void CleanSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetWidgetProperties(UIVBaseItemDA *NewItem, const uint8 NewAmount, const uint8 NewSlotIndex);
};