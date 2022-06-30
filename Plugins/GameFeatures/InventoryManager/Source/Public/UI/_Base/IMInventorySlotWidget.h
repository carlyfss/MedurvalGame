// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InventoryInterface.h"
#include "IMInventorySlotWidget.generated.h"

class UIMDetailWidget;
class UMDGameInstance;
class UIMBaseItemDA;
class UIMInventoryComponent;
class UTextBlock;
class UButton;
class UImage;

UCLASS(meta = (DisplayName = "InventorySlotWidget"))
class UIMInventorySlotWidget final : public UUserWidget, public IInventoryInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintGetter = GetItem)
	TObjectPtr<UIMBaseItemDA> Item = nullptr;

	UPROPERTY(Transient, BlueprintGetter = GetAmount)
	uint8 Amount;

	UPROPERTY(Transient, BlueprintGetter = GetSlotIndex)
	uint8 SlotIndex;

	UPROPERTY(Transient, BlueprintSetter = SetInventoryReference, BlueprintGetter = GetInventoryReference)
	TObjectPtr<UIMInventoryComponent> InventoryReference;

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
	TObjectPtr<UIMDetailWidget> DetailWidget = nullptr;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "InventorySlot")
	void CreateDetailWidget();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetInventoryReference(UIMInventoryComponent *TargetInventory);

	void SetAmount(const uint8 NewAmount);

	void SetItem(UIMBaseItemDA *NewItem);

public:
	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot")
	void CleanSlot();

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Setter")
	void SetWidgetProperties(UIMBaseItemDA *NewItem, const uint8 NewAmount, const uint8 NewSlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	UButton *GetSlotButton() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	UIMInventoryComponent *GetInventoryReference() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	uint8 GetAmount() const;

	UFUNCTION(BlueprintCallable, Category = "InventorySlot|Getter")
	UIMBaseItemDA *GetItem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InventorySlot|Getter")
	uint8 GetSlotIndex() const;
};