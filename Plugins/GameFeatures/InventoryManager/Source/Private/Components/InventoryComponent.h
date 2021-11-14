// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Structs/InventorySlot.h"
#include "InventoryComponent.generated.h"

class UBaseInventoryWidget;
class ACharacter;
class UBaseItemDA;

UCLASS(BlueprintType, Blueprintable, meta=(DisplayName="InventoryComponent"))
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetSlotAmount, Category="_Inventory|Configuration")
	uint8 SlotAmount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetSlotsPerRow, Category="_Inventory|Configuration")
	uint8 SlotPerRow = 4;

	UPROPERTY(EditDefaultsOnly, Category="_Inventory|Configuration")
	uint8 MaxStackSize = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetIsVisible, BlueprintSetter=SetIsVisible,
		Category="_Inventory|Configuration", meta=(AllowPrivateAccess=true))
	bool bIsVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Inventory|Configuration", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> InventoryWidgetClass = nullptr;

	UPROPERTY(BlueprintSetter=SetInventoryWidget, BlueprintGetter=GetInventoryWidget,
		Category="_Inventory|Configuration")
	TObjectPtr<UBaseInventoryWidget> InventoryWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="_Inventory", meta=(AllowPrivateAccess=true))
	TArray<FInventorySlot> Slots;

public:
	// Sets default values for this actor's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category="_Inventory")
	bool IsSlotEmpty(const int32 Index) const;

	UFUNCTION(BlueprintCallable, Category="_Inventory")
	TSoftObjectPtr<UBaseItemDA> GetItemInfoAtIndex(const int32 Index, bool& bIsSlotEmpty, uint8& Amount) const;

	UFUNCTION(BlueprintCallable, Category="_Inventory")
	int GetAmountAtIndex(const int32 Index) const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="_Inventory")
	void UpdateSlotAtIndex(int32 Index);

protected:
	bool SearchEmptySlot(int32& Index);

	bool SearchFreeStack(const TSoftObjectPtr<UBaseItemDA> ItemData, int32& Index);

	bool AddUnstackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, uint8 Amount, uint8& Rest);

	bool AddStackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, uint8 Amount, uint8& Rest);

	bool RemoveItemAtIndex(const int32 Index, const uint8 Amount);

	bool SwapSlots(const int32 OriginIndex, const int32 TargetIndex);

	bool SplitStack(const int32 Index, int32 Amount);

public:
	UFUNCTION(BlueprintCallable, Category="_Inventory|Interaction")
	bool AddItem(const TSoftObjectPtr<UBaseItemDA> ItemClass, uint8 Amount, uint8& Rest);

	UFUNCTION(BlueprintImplementableEvent, Category="_Inventory|Interaction")
	void UseItemAtIndex(int32 Index);
	
	UFUNCTION(BlueprintImplementableEvent, Category="_Inventory|Visibility")
	void ShowInventory() const;

	UFUNCTION(BlueprintImplementableEvent, Category="_Inventory|Visibility")
	void HideInventory() const;
	
#pragma region Setters
	UFUNCTION(BlueprintCallable, Category="_Inventory|Setters")
	void SetSlotAmount(const uint8 AmountOfSlots);

	UFUNCTION(BlueprintCallable, Category="_Inventory|Setters")
	void SetMaxStackSize(const uint8 StackSize);

	UFUNCTION(BlueprintCallable, Category="_Inventory|Setters")
	void SetInventoryWidget(UBaseInventoryWidget* InventoryWidgetRef);

	UFUNCTION(BlueprintCallable, Category="_Inventory|Setters")
	void SetIsVisible(bool bIsInventoryVisible);
#pragma endregion Setters

#pragma region Getters
	UFUNCTION(BlueprintCallable, Category="_Inventory|Getters")
	TArray<FInventorySlot> GetInventorySlots() const;

	UFUNCTION(BlueprintCallable, Category="_Inventory|Getters")
	uint8 GetSlotsPerRow() const;

	UFUNCTION(BlueprintCallable, Category="_Inventory|Getters")
	uint8 GetSlotAmount() const;

	UFUNCTION(BlueprintCallable, Category="_Inventory|Getters")
	UBaseInventoryWidget* GetInventoryWidget() const;

	UFUNCTION(BlueprintCallable, Category="_Inventory|Getters")
	bool GetIsVisible() const;
#pragma endregion Setters

	
};
