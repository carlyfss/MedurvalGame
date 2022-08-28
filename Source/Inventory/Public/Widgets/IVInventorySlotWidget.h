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

	UPROPERTY(Transient, BlueprintGetter = GetItem)
	TObjectPtr<UIVBaseItemDA> Item = nullptr;

	UPROPERTY(Transient, BlueprintGetter = GetAmount)
	uint8 Amount;

	UPROPERTY(Transient, BlueprintGetter = GetSlotIndex)
	uint8 SlotIndex;

	UPROPERTY(Transient, BlueprintSetter = SetInventoryReference, BlueprintGetter = GetInventoryReference)
	TObjectPtr<UIVInventoryComponent> InventoryReference;

	// Widget Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InventorySlot",
			  meta = (BindWidget, AllowPrivateAccess = true))
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

public:
	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void CleanSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetWidgetProperties(UIVBaseItemDA *NewItem, const uint8 NewAmount, const uint8 NewSlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	UButton *GetSlotButton() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	UIVInventoryComponent *GetInventoryReference() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	uint8 GetAmount() const;

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Getter")
	UIVBaseItemDA *GetItem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	uint8 GetSlotIndex() const;
};