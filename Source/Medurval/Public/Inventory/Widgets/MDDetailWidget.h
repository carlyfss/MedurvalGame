// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "MDDetailWidget.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;
class UMDItemDataAsset;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS(meta = (DisplayName = "MDDetailWidget"))
class MEDURVAL_API UMDDetailWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="MDDetailWidget", meta=(AllowPrivateAccess=true))
	FMDInventorySlot SlotInfo;

	UPROPERTY(BlueprintReadWrite, Category="MDDetailWidget", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDItemDataAsset> Item = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDDetailWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCommonLazyImage> Icon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDDetailWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCommonTextBlock> Name = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDDetailWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCommonTextBlock> Category = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDDetailWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCommonTextBlock> Description = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category="DraggedItem")
	void SetSlotInfo(FMDInventorySlot NewSlotInfo);

};