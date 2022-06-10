// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/MDDataAssetInterface.h"
#include "IMInventoryWidget.generated.h"

class UIMInventorySlotWidget;
class UIMInventoryComponent;
class UUniformGridPanel;
/**
 * 
 */
UCLASS(meta=(DisplayName="InventoryWidget"))
class UIMInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	IMDDataAssetInterface* DAInt;

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UUniformGridPanel> SlotPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UIMInventoryComponent> InventoryReference = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	uint8 SlotsPerRow = 4;

	UPROPERTY(BlueprintReadWrite, Category="_InventoryWidget", meta=(AllowPrivateAccess=true))
	TArray<UIMInventorySlotWidget*> SlotWidgets;

public:
	TArray<UIMInventorySlotWidget*> GetSlotWidgets();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="_InventoryWidget")
	void GenerateSlotWidgets();

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetInventoryReference(UIMInventoryComponent* InventoryRef);

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	void SetSlotsPerRow(uint8 Slots);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="_InventoryWidget")
	void OnSlotClicked(UIMInventorySlotWidget* SlotInfo);

	UFUNCTION(BlueprintCallable, Category="_InventoryWidget")
	FVector2D CalculateActionMenuLocation(int32 Row, int32 Column, float ScrollOffset) const;
};
