// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "IMInventoryWidget.generated.h"

class UIMInventorySlotWidget;
class UIMInventoryComponent;
class UUniformGridPanel;
/**
 *
 */
UCLASS(meta = (DisplayName = "InventoryWidget"))
class UIMInventoryWidget : public UCBCommonActivatableWidget
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UUniformGridPanel> SlotPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UIMInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category = "InventoryWidget", meta = (AllowPrivateAccess = true))
	TArray<UIMInventorySlotWidget *> SlotWidgets;

protected:
	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetInventoryReference(UIMInventoryComponent *InventoryRef);

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);

public:
	TArray<UIMInventorySlotWidget *> GetSlotWidgets();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category = "InventoryWidget")
	void UpdateSlotAtIndex(uint8 SlotIndex);
};
