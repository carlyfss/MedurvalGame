// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "IVDetailWidget.generated.h"

class UIVBaseItemDA;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DetailWidget"))
class INVENTORY_API UIVDetailWidget : public UCBCommonActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
    TObjectPtr<UIVBaseItemDA> ItemInfo = nullptr;

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
    void SetItemInfo(UIVBaseItemDA *Item);

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="_Item")
    UIVBaseItemDA *GetItemInfo() const;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="DraggedItem")
    void UpdateWidget();
};
