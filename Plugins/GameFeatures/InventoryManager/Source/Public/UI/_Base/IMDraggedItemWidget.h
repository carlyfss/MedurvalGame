// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "IMDraggedItemWidget.generated.h"

class UIMBaseItemDA;
class UIMInventoryComponent;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DraggedItemWidget"))
class INVENTORYMANAGER_API UIMDraggedItemWidget : public UCBCommonActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
    TObjectPtr<UIMBaseItemDA> ItemInfo = nullptr;

    UPROPERTY(Transient)
    int SlotIndex = 0;

    UPROPERTY(Transient, BlueprintGetter=GetAmount, BlueprintSetter=SetAmount)
    uint8 Amount;

    UPROPERTY(Transient, BlueprintGetter=GetInventoryReference, BlueprintSetter=SetInventoryReference)
    TObjectPtr<UIMInventoryComponent> InventoryReference;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DraggedItem", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UImage> ItemIcon = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DraggedItem", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UTextBlock> AmountText = nullptr;

    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetItemInfo(UIMBaseItemDA *Item);

    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetAmount(uint8 DraggedAmount);

    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetInventoryReference(UIMInventoryComponent *InventoryRef);

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
    UIMInventoryComponent *GetInventoryReference() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
    UIMBaseItemDA *GetItemInfo() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
    uint8 GetAmount() const;
};
