// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "MDDetailWidget.generated.h"

class UMDItemDataAsset;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS(meta = (DisplayName = "DetailWidget"))
class MEDURVAL_API UMDDetailWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintGetter=GetItemInfo, BlueprintSetter=SetItemInfo)
	TObjectPtr<UMDItemDataAsset> ItemInfo = nullptr;

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
	void SetItemInfo(UMDItemDataAsset* Item);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="_Item")
	UMDItemDataAsset* GetItemInfo() const;
};
