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

	UPROPERTY(Transient)
	TObjectPtr<UInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(Transient)
	uint8 SlotsPerRow = 4;

	UPROPERTY(Transient)
	TArray<UBaseInventorySlotWidget*> SlotsWidgets;

public:

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetInventoryReference(UInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);
	
	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetSlotColumnAndRow(int32 Index, uint8& Column, uint8& Row) const;
};
