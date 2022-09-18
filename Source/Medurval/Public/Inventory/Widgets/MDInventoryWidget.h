// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "MDInventoryWidget.generated.h"

class UMDInventorySlotWidget;
class UMDInventoryComponent;
class UUniformGridPanel;
/**
 *
 */
UCLASS(meta = (DisplayName = "InventoryWidget"))
class MEDURVAL_API UMDInventoryWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UUniformGridPanel> SlotPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UMDInventorySlotWidget*> SlotWidgets;

protected:
	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetInventoryReference(UMDInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);

public:
	TArray<UMDInventorySlotWidget*> GetSlotWidgets();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateSlotAtIndex(uint8 SlotIndex);
};
