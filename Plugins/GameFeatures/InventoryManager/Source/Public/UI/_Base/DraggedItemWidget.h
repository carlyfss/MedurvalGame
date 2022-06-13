// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggedItemWidget.generated.h"

class UIMBaseItemDA;
class UIMInventoryComponent;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class INVENTORYMANAGER_API UDraggedItemWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
	TObjectPtr<UIMBaseItemDA> ItemInfo = nullptr;

private:
	UPROPERTY(Transient)
	int SlotIndex = 0;

	UPROPERTY(Transient, BlueprintGetter=GetAmount, BlueprintSetter=SetAmount)
	uint8 Amount;

	UPROPERTY(Transient, BlueprintGetter=GetInventoryReference, BlueprintSetter=SetInventoryReference)
	TObjectPtr<UIMInventoryComponent> InventoryReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UImage> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> AmountText = nullptr;


public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
	UIMBaseItemDA* GetItemInfo() const;

	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetItemInfo(UIMBaseItemDA* Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
	uint8 GetAmount() const;

	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetAmount(uint8 DraggedAmount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
	UIMInventoryComponent* GetInventoryReference() const;

	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetInventoryReference(UIMInventoryComponent* InventoryRef);
};
