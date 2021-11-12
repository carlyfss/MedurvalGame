// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInventoryWidget.generated.h"

class UBaseInventorySlotWidget;
class UInventoryComponent;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class UBaseInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UUniformGridPanel> SlotPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category="_InventoryWidget", meta=(AllowPrivateAccess=true))
	TArray<UBaseInventorySlotWidget*> SlotWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="_InventoryWidget", meta=(AllowPrivateAccess=true))
	TSubclassOf<UBaseInventorySlotWidget> SlotWidgetClass = nullptr;

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="_InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetInventoryReference(UInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);
};
