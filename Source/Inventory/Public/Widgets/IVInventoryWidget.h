// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "IVInventoryWidget.generated.h"

class UIVInventorySlotWidget;
class UIVInventoryComponent;
class UUniformGridPanel;
/**
 *
 */
UCLASS(meta = (DisplayName = "InventoryWidget"))
class INVENTORY_API UIVInventoryWidget : public UCBCommonActivatableWidget
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UUniformGridPanel> SlotPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UIVInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UIVInventorySlotWidget *> SlotWidgets;

protected:
	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetInventoryReference(UIVInventoryComponent *InventoryRef);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);

public:
	TArray<UIVInventorySlotWidget *> GetSlotWidgets();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateSlotAtIndex(uint8 SlotIndex);
};
