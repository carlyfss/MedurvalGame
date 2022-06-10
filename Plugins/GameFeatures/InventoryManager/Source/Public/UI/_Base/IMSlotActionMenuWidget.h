// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMSlotActionMenuWidget.generated.h"

class UIMBaseItemDA;
class UIMInventoryComponent;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS(meta=(DisplayName="InventorySlotActionMenuWidget"))
class UIMSlotActionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_ActionMenu", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UButton> UseButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_ActionMenu", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UButton> DiscardButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_ActionMenu", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UButton> SplitButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_ActionMenu", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UButton> CancelButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_ActionMenu", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> UseItemText = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="_ActionMenu", meta=(AllowPrivateAccess=true))
	TObjectPtr<UIMInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="_ActionMenu", meta=(AllowPrivateAccess=true))
	TSoftObjectPtr<UIMBaseItemDA> ItemData = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="_ActionMenu", meta=(AllowPrivateAccess=true))
	int32 CurrentIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category="_ActionMenu", meta=(AllowPrivateAccess=true))
	uint8 Amount = 0;

protected:

	UFUNCTION(BlueprintCallable, Category="_ActionMenu")
	void Update(const int32 Index);
};

