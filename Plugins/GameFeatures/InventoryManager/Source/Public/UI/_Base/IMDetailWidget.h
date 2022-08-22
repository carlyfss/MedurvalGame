// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "IMDetailWidget.generated.h"

class UIMBaseItemDA;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DetailWidget"))
class INVENTORYMANAGER_API UIMDetailWidget : public UCBCommonActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
    TObjectPtr<UIMBaseItemDA> ItemInfo = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="_Item", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UImage> ItemIcon = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="_Item", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UTextBlock> ItemName = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="_Item", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UTextBlock> ItemCategory = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="_Item", meta=(BindWidget, AllowPrivateAccess=true))
    TObjectPtr<UTextBlock> ItemDescription = nullptr;

protected:
    UFUNCTION(BlueprintCallable, Category="DraggedItem")
    void SetItemInfo(UIMBaseItemDA *Item);

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="_Item")
    UIMBaseItemDA *GetItemInfo() const;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="DraggedItem")
    void UpdateWidget();
};
