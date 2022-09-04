// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "Components/CBActorComponent.h"
#include "CoreMinimal.h"
#include "Interfaces/IVInventoryInterface.h"
#include "Structs/IVInventorySlot.h"
#include "IVInventoryComponent.generated.h"

class AMDBaseCharacter;
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
    TObjectPtr<AMDBaseCharacter> PlayerCharacter = nullptr;

#pragma region Configurations
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
    uint8 SlotAmount = 15;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
    uint8 SlotPerRow = 5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
    uint8 MaxStackSize = 30;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
    bool bIsVisible = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> InventoryWidgetClass = nullptr;

    UPROPERTY(BlueprintReadWrite, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
    TObjectPtr<UIVInventoryWidget> InventoryWidget = nullptr;
#pragma endregion Configurations

    UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
    TArray<FIVInventorySlot> Slots;

protected:
    virtual void BeginPlay() override;

    bool SearchEmptySlot(uint8 &Index);

    bool SearchFreeStack(UIVBaseItemDA *Item, uint8 &Index);

    bool AddUnstackableItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest);

    bool AddStackableItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest);

#pragma region Interaction
    UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
    bool AddItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest);

    bool LoadAndAddItem(FPrimaryAssetId TargetItemId, uint8 Amount);
    
    void AddItemOnLoadCompleted(FPrimaryAssetId TargetItemId, uint8 Amount);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
    bool AddToIndex(uint8 SourceIndex, uint8 TargetIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
    bool RemoveItemAtIndex(uint8 Index, uint8 Amount);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
    bool SwapSlots(uint8 OriginIndex, uint8 TargetIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
    bool SplitStack(uint8 Index);

    UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
    bool SplitStackToIndex(uint8 SourceIndex, uint8 TargetIndex, uint8 Amount);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory|Interaction")
    void UseItemAtIndex(uint8 Index);
#pragma endregion Interaction

#pragma region Visibility
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory|Visibility")
    void ShowInventory();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory|Visibility")
    void HideInventory();
#pragma endregion Visibility

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool IsSlotEmpty(uint8 Index) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    UIVBaseItemDA *GetItemInfoAtIndex(uint8 Index, bool &bIsSlotEmpty, uint8 &Amount) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    uint8 GetAmountAtIndex(uint8 Index) const;

    TArray<FIVInventorySlot> GetSlots() const;

#pragma region Delegates
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UIVBaseItemDA *, ItemAdded, uint8, Amount);
    UPROPERTY(BlueprintAssignable)
    FOnItemAdded OnItemAdded;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemRemoved, UIVBaseItemDA *, ItemRemoved, uint8, Amount);
    UPROPERTY(BlueprintAssignable)
    FOnItemRemoved OnItemRemoved;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateSlotAtIndex, uint8, SlotIndex);
    UPROPERTY(BlueprintAssignable)
    FOnUpdateSlotAtIndex OnUpdateSlotAtIndex;
#pragma endregion Delegate;

    virtual bool OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd, uint8 Amount) override;

    virtual void UpdateSlotAfterLoad_Implementation(uint8 SlotIndex) override;
};
