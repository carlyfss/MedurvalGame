// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "Components/CBActorComponent.h"
#include "CoreMinimal.h"
#include "InputAction.h"
#include "Interfaces/IVInventoryInterface.h"
#include "Structs/IVInventorySlot.h"
#include "IVInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UIVBaseItemDA *, ItemAdded, uint8, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, UIVBaseItemDA *, ItemRemoved, uint8, Amount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateSlotAtIndex, uint8, SlotIndex);

class UIVInventoryWidget;
class ACharacter;
class UIVBaseItemDA;
class UInputMappingContext;

UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "InventoryComponent"))
class UIVInventoryComponent : public UCBActorComponent, public IIVInventoryInterface
{
    GENERATED_BODY()

    FCriticalSection SocketsCriticalSection;

    UPROPERTY(Transient)
    TObjectPtr<ACharacter> PlayerCharacter = nullptr;

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
    TObjectPtr<UIVInventoryWidget> InventoryWidget = nullptr;
#pragma endregion Configurations

#pragma region Inputs
    UPROPERTY(Transient)
    UEnhancedInputComponent *EnhancedInputComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "_Inventory|Inputs", meta = (AllowPrivateAccess = true))
    UInputMappingContext *InventoryMappingContext = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "_Inventory|Inputs", meta = (AllowPrivateAccess = true))
    TObjectPtr<UInputAction> ToggleInventoryAction;

    int ToggleInventoryBindingHandle;
#pragma endregion Inputs

    UPROPERTY(BlueprintReadWrite, Category = "_Inventory", meta = (AllowPrivateAccess = true))
    TArray<FIVInventorySlot> Slots;

protected:
    virtual void OnRegister() override;

    virtual void OnUnregister() override;

    bool SearchEmptySlot(uint8 &Index);

    bool SearchFreeStack(UIVBaseItemDA *Item, uint8 &Index);

    bool AddUnstackableItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest);

    bool AddStackableItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest);

#pragma region Interaction
    UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
    bool AddItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest);

    bool LoadAndAddItem(FPrimaryAssetId TargetItemId, uint8 Amount);
    
    void AddItemOnLoadCompleted(FPrimaryAssetId TargetItemId, uint8 Amount);

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
    bool AddToIndex(uint8 SourceIndex, uint8 TargetIndex);

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
    bool RemoveItemAtIndex(uint8 Index, uint8 Amount);

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
    bool SwapSlots(uint8 OriginIndex, uint8 TargetIndex);

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
    bool SplitStack(uint8 Index);

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Interaction")
    bool SplitStackToIndex(uint8 SourceIndex, uint8 TargetIndex, uint8 Amount);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "_Inventory|Interaction")
    void UseItemAtIndex(uint8 Index);
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
    void SetInventoryWidget(UIVInventoryWidget *InventoryWidgetRef);

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Setters")
    void SetIsVisible(bool bIsInventoryVisible);
#pragma endregion Setters

public:
    UFUNCTION(BlueprintCallable, Category = "_Inventory")
    bool IsSlotEmpty(uint8 Index) const;

    UFUNCTION(BlueprintCallable, Category = "_Inventory")
    UIVBaseItemDA *GetItemInfoAtIndex(uint8 Index, bool &bIsSlotEmpty, uint8 &Amount) const;

    UFUNCTION(BlueprintCallable, Category = "_Inventory")
    uint8 GetAmountAtIndex(uint8 Index) const;

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
    TArray<FIVInventorySlot> GetInventorySlots() const;

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
    uint8 GetSlotsPerRow() const;

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
    uint8 GetSlotAmount() const;

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
    UIVInventoryWidget *GetInventoryWidget() const;

    UFUNCTION(BlueprintCallable, Category = "_Inventory|Getters")
    bool GetIsVisible() const;
#pragma endregion Setters

#pragma region Inputs
    UFUNCTION(BlueprintImplementableEvent, Category = "_Inventory|Inputs")
    void OnToggleInventory(const FInputActionInstance &InputInstance);
#pragma endregion Inputs

    virtual bool OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd, uint8 Amount) override;

    virtual void UpdateSlotAfterLoad_Implementation(uint8 SlotIndex) override;
};
