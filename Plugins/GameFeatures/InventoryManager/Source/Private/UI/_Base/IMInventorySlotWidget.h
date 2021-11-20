// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMInventorySlotWidget.generated.h"

class UIMInventoryComponent;
class UBaseItemPrimaryDA;
class UTextBlock;
class UButton;
class UImage;

UCLASS(meta=(DisplayName="InventorySlotWidget"))
class UIMInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintGetter=GetItemDataAtSlot)
	TObjectPtr<UBaseItemPrimaryDA> ItemAtSlot = nullptr;

	UPROPERTY(Transient, BlueprintGetter=GetSlotIndex, BlueprintSetter=SetSlotIndex)
	int32 SlotIndex = 0;

	UPROPERTY(Transient)
	TSoftObjectPtr<UBaseItemPrimaryDA> ItemData = nullptr;

	UPROPERTY(Transient, BlueprintGetter=GetAmount)
	uint8 Amount;

	UPROPERTY(Transient, BlueprintSetter=SetInventoryReference, BlueprintGetter=GetInventoryReference)
	TObjectPtr<UIMInventoryComponent> InventoryReference;
	
	// Widget Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=tru))
	UButton* SlotButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=tru))
	UImage* ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=true))
	UTextBlock* AmountText = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category="_InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetInventoryReference(UIMInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	UIMInventoryComponent* GetInventoryReference() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	uint8 GetAmount() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	int32 GetSlotIndex() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetSlotIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	UBaseItemPrimaryDA* GetItemDataAtSlot() const;
};