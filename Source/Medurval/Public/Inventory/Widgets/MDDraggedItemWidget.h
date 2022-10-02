// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "MDDraggedItemWidget.generated.h"

class UCommonNumericTextBlock;
class UCommonLazyImage;
class UMDItemDataAsset;
class UMDInventoryComponent;

/**
 * 
 */
UCLASS(meta = (DisplayName = "MDDraggedItemWidget"))
class MEDURVAL_API UMDDraggedItemWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "MDDraggedItemWidget", meta = (AllowPrivateAccess = true))
	FMDInventorySlot SlotInfo = FMDInventorySlot();

	UPROPERTY(BlueprintReadWrite, Category="MDDetailWidget", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDItemDataAsset> Item = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="MDDraggedItemWidget", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDInventoryComponent> InventoryReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDDraggedItemWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCommonLazyImage> Icon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MDDraggedItemWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCommonNumericTextBlock> Amount = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category="MDDraggedItemWidget")
	void SetInventoryReference(UMDInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category="MDDraggedItemWidget")
	void SetSlotInfo(FMDInventorySlot NewSlotInfo);

};
