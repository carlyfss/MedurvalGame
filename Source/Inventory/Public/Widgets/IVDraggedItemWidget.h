// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "IVDraggedItemWidget.generated.h"

class UIVBaseItemDA;
class UIVInventoryComponent;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DraggedItemWidget"))
class INVENTORY_API UIVDraggedItemWidget : public UMDActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
    TObjectPtr<UIVBaseItemDA> ItemInfo = nullptr;

    UPROPERTY(Transient)
    int SlotIndex = 0;

    UPROPERTY(Transient, BlueprintGetter=GetAmount, BlueprintSetter=SetAmount)
    uint8 Amount;

    UPROPERTY(Transient, BlueprintGetter=GetInventoryReference, BlueprintSetter=SetInventoryReference)
    TObjectPtr<UIVInventoryComponent> InventoryReference;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DraggedItem", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UImage> ItemIcon = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="DraggedItem", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UTextBlock> AmountText = nullptr;

    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetItemInfo(UIVBaseItemDA* Item);

    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetAmount(uint8 DraggedAmount);

    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetInventoryReference(UIVInventoryComponent* InventoryRef);

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
    UIVInventoryComponent* GetInventoryReference() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
    UIVBaseItemDA* GetItemInfo() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="DraggedItem")
    uint8 GetAmount() const;
};
