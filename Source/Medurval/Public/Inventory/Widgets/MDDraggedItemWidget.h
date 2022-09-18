// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "MDDraggedItemWidget.generated.h"

class UMDItemDataAsset;
class UMDInventoryComponent;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DraggedItemWidget"))
class MEDURVAL_API UMDDraggedItemWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
	TObjectPtr<UMDItemDataAsset> ItemInfo = nullptr;

	UPROPERTY(Transient)
	int SlotIndex = 0;

	UPROPERTY(Transient, BlueprintGetter=GetAmount, BlueprintSetter=SetAmount)
	uint8 Amount;

	UPROPERTY(Transient, BlueprintGetter=GetInventoryReference, BlueprintSetter=SetInventoryReference)
	TObjectPtr<UMDInventoryComponent> InventoryReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DraggedItem", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UImage> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DraggedItem", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> AmountText = nullptr;

	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetItemInfo(UMDItemDataAsset* Item);

	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetAmount(uint8 DraggedAmount);

	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetInventoryReference(UMDInventoryComponent* InventoryRef);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
	UMDInventoryComponent* GetInventoryReference() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
	UMDItemDataAsset* GetItemInfo() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
	uint8 GetAmount() const;
};
