// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/CBActorComponent.h"
#include "Interfaces/InventoryInterface.h"
#include "Structs/IMInventorySlot.h"
#include "IMInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UIMBaseItemDA *, ItemAdded, uint8, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, UIMBaseItemDA *, ItemRemoved, uint8, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateSlotAtIndex, uint8, SlotIndex);

class UIMInventoryWidget;
class ACharacter;
class UIMBaseItemDA;
class UInputMappingContext;

UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "InventoryComponent"))
class UIMInventoryComponent : public UCBActorComponent, public IInventoryInterface
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(Transient)
	ACharacter *PlayerCharacter = nullptr;

#pragma region Configurations
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetSlotAmount, Category = "_Inventory|Configuration")
	uint8 SlotAmount = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetSlotsPerRow, Category = "_Inventory|Configuration")
	uint8 SlotPerRow = 5;

	UPROPERTY(EditDefaultsOnly, Category = "_Inventory|Configuration")
	uint8 MaxStackSize = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetIsVisible, BlueprintSetter = SetIsVisible,
						Category = "_Inventory|Configuration", meta = (AllowPrivateAccess = true))
	bool bIsVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Inventory|Configuration", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> InventoryWidgetClass = nullptr;

	UPROPERTY(BlueprintSetter = SetInventoryWidget, BlueprintGetter = GetInventoryWidget,
						Category = "_Inventory|Configuration")
	TObjectPtr<UIMInventoryWidget> InventoryWidget = nullptr;
#pragma endregion Configurations

#pragma region Inputs
	UPROPERTY(Transient)
	UEnhancedInputComponent *EnhancedInputComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "_Inventory|Inputs", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> InventoryMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "_Inventory|Inputs", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> ToggleInventoryAction;

	uint32 ToggleInventoryBindingHandle;
#pragma endregion Inputs

	UPROPERTY(BlueprintReadWrite, Category = "_Inventory", meta = (AllowPrivateAccess = true))
	TArray<FIMInventorySlot> Slots;

protected:
	virtual void OnRegister() override;

	virtual void OnUnregister() override;

	bool SearchEmptySlot(int32 &Index);

	bool SearchFreeStack(UIMBaseItemDA *Item, int32 &Index);

	bool AddUnstackableItem(UIMBaseItemDA *Item, uint8 Amount, uint8 &Rest);

	bool AddStackableItem(UIMBaseItemDA *Item, uint8 Amount, uint8 &Rest);

#pragma region Interaction
	UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
	bool AddItem(UIMBaseItemDA *Item, uint8 Amount, uint8 &Rest);

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
	bool AddToIndex(uint8 SourceIndex, uint8 TargetIndex);

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
	bool RemoveItemAtIndex(const int32 Index, const uint8 Amount);

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
	bool SwapSlots(const int32 OriginIndex, const int32 TargetIndex);

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
	bool SplitStack(const int32 Index);

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
	bool SplitStackToIndex(const int32 SourceIndex, const int32 TargetIndex, uint8 Amount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "_Inventory|Interaction")
	void UseItemAtIndex(int32 Index);
#pragma endregion Interaction

#pragma region Visibility
	UFUNCTION(BlueprintImplementableEvent, Category = "_Inventory|Visibility")
	void ShowInventory() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "_Inventory|Visibility")
	void HideInventory() const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Visibility")
	void ToggleInventory();
#pragma endregion Visibility

#pragma region Setters
	UFUNCTION(BlueprintCallable, Category = "_Inventory|Setters")
	void SetInventoryWidget(UIMInventoryWidget *InventoryWidgetRef);

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Setters")
	void SetIsVisible(bool bIsInventoryVisible);
#pragma endregion Setters

	UPROPERTY()

public:
	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	bool IsSlotEmpty(const int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	UIMBaseItemDA *GetItemInfoAtIndex(const int32 Index, bool &bIsSlotEmpty, uint8 &Amount) const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	int GetAmountAtIndex(const int32 Index) const;

#pragma region Delegates
	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateSlotAtIndex OnUpdateSlotAtIndex;
#pragma endregion Delegate;

#pragma region Getters
	UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
	TArray<FIMInventorySlot> GetInventorySlots() const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
	uint8 GetSlotsPerRow() const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
	uint8 GetSlotAmount() const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
	UIMInventoryWidget *GetInventoryWidget() const;

	UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
	bool GetIsVisible() const;
#pragma endregion Setters

#pragma region Inputs
	UFUNCTION(BlueprintImplementableEvent, Category = "_Inventory|Inputs")
	void OnToggleInventory(const FInputActionInstance &InputInstance);
#pragma endregion Inputs

	virtual bool OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd) override;

	void AfterLoad();

	FPrimaryAssetId ItemIdToAddInv;

	virtual void UpdateSlotAfterLoad_Implementation(uint8 SlotIndex) override;
};
