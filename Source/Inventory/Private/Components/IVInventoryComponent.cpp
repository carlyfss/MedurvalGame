// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Components/IVInventoryComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Items/IVBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/IVInventorySlotWidget.h"
#include "Widgets/IVInventoryWidget.h"

void UIVInventoryComponent::OnRegister()
{
    Super::OnRegister();

    PlayerCharacter = Cast<ACharacter>(GetOwner());

    if (!IsValid(PlayerCharacter))
        return;

    if (!IsValid(PlayerCharacter->InputComponent))
        return;

    EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerCharacter->InputComponent);

    if (!IsValid(EnhancedInputComponent))
        return;

    if (!ToggleInventoryAction)
        return;

    ToggleInventoryBindingHandle = EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered,
                                                                      this, &UIVInventoryComponent::OnToggleInventory)
                                       .GetHandle();
}

void UIVInventoryComponent::OnUnregister()
{
    Super::OnUnregister();

    if (EnhancedInputComponent != nullptr)
    {
        EnhancedInputComponent->RemoveBindingByHandle(ToggleInventoryBindingHandle);
    }

    PlayerCharacter = nullptr;
    EnhancedInputComponent = nullptr;
    InventoryWidgetClass = nullptr;
    InventoryWidget = nullptr;
}

/** Checks if a given index is empty or not */
bool UIVInventoryComponent::IsSlotEmpty(uint8 Index) const
{
    return Slots[Index].Item.IsNull();
}

/** Get item information at the given Index, if it doesn't find, it returns a
 * nullptr, and the bIsSlotEmpty = true */
UIVBaseItemDA *UIVInventoryComponent::GetItemInfoAtIndex(uint8 Index, bool &bIsSlotEmpty, uint8 &Amount) const
{
    check(Slots.Num() > Index);

    const FIVInventorySlot Slot = Slots[Index];

    if (IsValid(Slot.Item))
    {
        UIVBaseItemDA *ItemInfo = Slot.Item;
        Amount = Slot.Amount;
        bIsSlotEmpty = false;

        return ItemInfo;
    }

    bIsSlotEmpty = true;
    return nullptr;
}

uint8 UIVInventoryComponent::GetAmountAtIndex(uint8 Index) const
{
    check(Slots.Num() > Index) return Slots[Index].Amount;
}

void UIVInventoryComponent::ToggleInventory()
{
    if (bIsVisible)
    {
        HideInventory();
    }

    ShowInventory();
}

/** Searches for a empty slot, and if it finds, store the index in the parameter
 * &Index */
bool UIVInventoryComponent::SearchEmptySlot(uint8 &Index)
{
    bool bEmptySlot = false;
    uint8 FoundIndex = 0;

    if (!Slots.IsEmpty())
    {
        FScopeLock Lock(&SocketsCriticalSection);

        for (int i = 0; i < Slots.Num(); i++)
        {
            if (Slots[i].Item)
                continue;

            bEmptySlot = true;
            FoundIndex = i;
            break;
        }
    }
    else
    {
        bEmptySlot = true;
    }

    Index = FoundIndex;
    return bEmptySlot;
}

/** Searches for a empty slot, and if it finds, check the MaxStackSize of the
 * slot and stores the index in the parameter &Index and if the stack is full it
 * return false
 */
bool UIVInventoryComponent::SearchFreeStack(UIVBaseItemDA *Item, uint8 &Index)
{
    bool bSlotAvaiable = false;
    uint8 FoundIndex = 0;

    if (!Slots.IsEmpty())
    {
        FScopeLock Lock(&SocketsCriticalSection);

        for (int i = 0; i < Slots.Num(); i++)
        {
            if (Slots[i].Item && Slots[i].Item != Item)
                continue;
            if (Slots[i].Amount == MaxStackSize)
                continue;

            bSlotAvaiable = true;
            FoundIndex = i;
            break;
        }
    }

    Index = FoundIndex;

    return bSlotAvaiable;
}

bool UIVInventoryComponent::AddItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest)
{
    if (!Item)
        return false;

    if (!Item->bCanBeStacked)
    {
        OnItemAdded.Broadcast(Item, Amount);
        return AddUnstackableItem(Item, Amount, Rest);
    }

    OnItemAdded.Broadcast(Item, Amount);
    return AddStackableItem(Item, Amount, Rest);
}

bool UIVInventoryComponent::AddUnstackableItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest)
{
    FScopeLock Lock(&SocketsCriticalSection);

    bool bAddedSuccessfully = false;
    uint8 FoundIndex = 0;

    if (!SearchEmptySlot(FoundIndex))
    {
        Rest = Amount;
        bAddedSuccessfully = false;
    }
    else
    {
        Slots[FoundIndex].Item = Item;
        Slots[FoundIndex].Amount = 1;

        if (Amount > 1)
        {
            const uint8 NewAmount = Amount - 1;

            bAddedSuccessfully = AddItem(Item, NewAmount, Rest);
        }

        Rest = 0;
    }

    OnUpdateSlotAtIndex.Broadcast(FoundIndex);
    return bAddedSuccessfully;
}

bool UIVInventoryComponent::AddStackableItem(UIVBaseItemDA *Item, uint8 Amount, uint8 &Rest)
{
    FScopeLock Lock(&SocketsCriticalSection);

    bool bAddedSuccessfully = false;
    uint8 AmountRest = 0;
    uint8 FoundIndex = 0;

    if (!SearchFreeStack(Item, FoundIndex))
    {
        if (SearchEmptySlot(FoundIndex))
        {
            if (Amount > MaxStackSize)
            {
                Slots[FoundIndex].Item = Item;
                Slots[FoundIndex].Amount = MaxStackSize;

                const uint8 NewAmount = Amount - MaxStackSize;
                bAddedSuccessfully = AddItem(Item, NewAmount, AmountRest);
            }
            else
            {
                Slots[FoundIndex].Item = Item;
                Slots[FoundIndex].Amount = Amount;

                Rest = 0;
                bAddedSuccessfully = true;    
            }
        }
        else
        {
            Rest = Amount; 
        }
    }
    else
    {
        uint8 CurrentStackAmount = Slots[FoundIndex].Amount + Amount;

        if (CurrentStackAmount > MaxStackSize)
        {
            Slots[FoundIndex].Item = Item;
            Slots[FoundIndex].Amount = MaxStackSize;

            const uint8 RestAmount = CurrentStackAmount - MaxStackSize;
            bAddedSuccessfully = AddItem(Item, RestAmount, AmountRest);
        } else
        {
            Slots[FoundIndex].Item = Item;
            Slots[FoundIndex].Amount = CurrentStackAmount;
            bAddedSuccessfully = true;
        }
    }
    
    OnUpdateSlotAtIndex.Broadcast(FoundIndex);
    return bAddedSuccessfully;
}

bool UIVInventoryComponent::RemoveItemAtIndex(uint8 Index, uint8 Amount)
{
    if (!IsSlotEmpty(Index) && Amount > 0)
    {
        FScopeLock Lock(&SocketsCriticalSection);

        if (Amount >= GetAmountAtIndex(Index))
        {
            TArray<UIVInventorySlotWidget *> SlotWidgets = InventoryWidget->GetSlotWidgets();
            UIVInventorySlotWidget *SlotWidget = SlotWidgets[Index];

            Slots[Index].Item = nullptr;
            Slots[Index].Amount = 0;

            SlotWidget->CleanSlot();

            OnItemRemoved.Broadcast(Slots[Index].Item, Slots[Index].Amount);
            return true;
        }

        Slots[Index].Amount -= Amount;

        OnItemRemoved.Broadcast(Slots[Index].Item, Slots[Index].Amount);
        OnUpdateSlotAtIndex.Broadcast(Index);

        return true;
    }

    return false;
}

bool UIVInventoryComponent::SwapSlots(uint8 OriginIndex, uint8 TargetIndex)
{
    FScopeLock Lock(&SocketsCriticalSection);

    const uint8 SlotsLastIndex = Slots.Num() - 1;

    if (OriginIndex > SlotsLastIndex || TargetIndex > SlotsLastIndex)
    {
        return false;
    }

    const FIVInventorySlot TempSlot = Slots[TargetIndex];

    Slots[TargetIndex].Item = Slots[OriginIndex].Item;
    Slots[TargetIndex].Amount = Slots[OriginIndex].Amount;

    Slots[OriginIndex].Item = TempSlot.Item;
    Slots[OriginIndex].Amount = TempSlot.Amount;

    OnUpdateSlotAtIndex.Broadcast(OriginIndex);
    OnUpdateSlotAtIndex.Broadcast(TargetIndex);

    return true;
}

bool UIVInventoryComponent::SplitStack(uint8 Index)
{
    if (IsSlotEmpty(Index))
    {
        return false;
    }

    bool bIsSlotEmpty = false;
    uint8 CurrentAmount = 0;

    UIVBaseItemDA *ItemInfo = GetItemInfoAtIndex(Index, bIsSlotEmpty, CurrentAmount);

    if (!ItemInfo)
        return false;

    if (!ItemInfo->bCanBeStacked && CurrentAmount <= 1)
        return false;

    uint8 FoundSlotIndex = 0;
    uint8 HalfAmount = (CurrentAmount / 2);

    if (!SearchEmptySlot(FoundSlotIndex))
        return false;

    FScopeLock Lock(&SocketsCriticalSection);

    Slots[Index].Item = ItemInfo;
    Slots[Index].Amount = CurrentAmount - HalfAmount;

    Slots[FoundSlotIndex].Item = ItemInfo;
    Slots[FoundSlotIndex].Amount = HalfAmount;

    OnUpdateSlotAtIndex.Broadcast(Index);
    OnUpdateSlotAtIndex.Broadcast(FoundSlotIndex);
    return true;
}

bool UIVInventoryComponent::SplitStackToIndex(uint8 SourceIndex, uint8 TargetIndex, uint8 Amount)
{
    bool bIsSlotEmpty;
    uint8 AmountAtSlot;

    UIVBaseItemDA *ItemAtSourceSlot = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);

    bool bTargetSlotHasAmount = AmountAtSlot > 1;
    bool bIsAmountLessThanTargetAmount = AmountAtSlot > Amount;

    if (IsSlotEmpty(TargetIndex) && !IsSlotEmpty(SourceIndex) &&
        ItemAtSourceSlot->bCanBeStacked && bTargetSlotHasAmount &&
        bIsAmountLessThanTargetAmount)
    {
        Slots[SourceIndex].Amount -= Amount;
        Slots[TargetIndex].Item = ItemAtSourceSlot;
        Slots[TargetIndex].Amount = Amount;

        OnUpdateSlotAtIndex.Broadcast(SourceIndex);
        OnUpdateSlotAtIndex.Broadcast(TargetIndex);
        return true;
    }

    return false;
}

bool UIVInventoryComponent::LoadAndAddItem(FPrimaryAssetId TargetItemId, uint8 Amount)
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return false;

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UIVInventoryComponent::AddItemOnLoadCompleted, TargetItemId, Amount);

    AssetManager->LoadPrimaryAsset(TargetItemId, BundlesToLoad, Delegate);
    return true;
}

bool UIVInventoryComponent::OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd, uint8 Amount)
{
    return LoadAndAddItem(ItemIdToAdd, Amount);
}

void UIVInventoryComponent::AddItemOnLoadCompleted(FPrimaryAssetId TargetItemId, uint8 Amount)
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    UIVBaseItemDA *Item = Cast<UIVBaseItemDA>(AssetManager->GetPrimaryAssetObject(TargetItemId));

    if (!Item)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemID %s was not loaded yet!"), *TargetItemId.ToString());
        return;
    }

    uint8 Rest = 0;
    AddItem(Item, Amount, Rest);
}

bool UIVInventoryComponent::AddToIndex(uint8 SourceIndex, uint8 TargetIndex)
{
    const UClass *SourceSlotClass = Slots[SourceIndex].Item->GetClass();

    if (Slots[TargetIndex].Item)
    {
        const UClass *TargetSlotClass = Slots[TargetIndex].Item->GetClass();

        bool bIsClassEqual = SourceSlotClass == TargetSlotClass;
        bool bIsTargetLessThanMaxSize = Slots[TargetIndex].Amount < MaxStackSize;
        bool bIsSlotEmpty;

        uint8 AmountAtSlot;

        const UIVBaseItemDA *SourceItem = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);

        if (!bIsClassEqual && !bIsTargetLessThanMaxSize && !SourceItem->bCanBeStacked)
        {
            return false;
        }
    }

    uint8 TargetTotalRestAmount = MaxStackSize - GetAmountAtIndex(TargetIndex);
    uint8 SourceAmount = GetAmountAtIndex(SourceIndex);

    if (TargetTotalRestAmount <= SourceAmount)
    {
        uint8 SourceRestAmount = GetAmountAtIndex(SourceIndex) - (MaxStackSize - GetAmountAtIndex(TargetIndex));

        Slots[SourceIndex].Amount = SourceRestAmount;

        Slots[TargetIndex].Item = Slots[SourceIndex].Item;
        Slots[TargetIndex].Amount = MaxStackSize;
    }
    else
    {
        uint8 NewTotalAmount = GetAmountAtIndex(SourceIndex) + GetAmountAtIndex(TargetIndex);

        Slots[TargetIndex].Item = Slots[SourceIndex].Item;
        Slots[TargetIndex].Amount = NewTotalAmount;

        Slots[SourceIndex].Item = nullptr;
        Slots[SourceIndex].Amount = 0;
    }

    OnUpdateSlotAtIndex.Broadcast(SourceIndex);
    OnUpdateSlotAtIndex.Broadcast(TargetIndex);

    return true;
}
#pragma endregion InventoryInteractions

void UIVInventoryComponent::UpdateSlotAfterLoad_Implementation(uint8 SlotIndex)
{
    TArray<UIVInventorySlotWidget *> SlotWidgets = InventoryWidget->GetSlotWidgets();
    UIVInventorySlotWidget *SlotWidget = SlotWidgets[SlotIndex];

    SlotWidget->UpdateSlot();
}

TArray<FIVInventorySlot> UIVInventoryComponent::GetInventorySlots() const
{
    return Slots;
}

uint8 UIVInventoryComponent::GetSlotsPerRow() const { return SlotPerRow; }

uint8 UIVInventoryComponent::GetSlotAmount() const { return SlotAmount; }

void UIVInventoryComponent::SetInventoryWidget(UIVInventoryWidget *InventoryWidgetRef)
{
    InventoryWidget = InventoryWidgetRef;
}

void UIVInventoryComponent::SetIsVisible(bool bIsInventoryVisible)
{
    bIsVisible = bIsInventoryVisible;
}

bool UIVInventoryComponent::GetIsVisible() const { return bIsVisible; }

UIVInventoryWidget *UIVInventoryComponent::GetInventoryWidget() const
{
    return InventoryWidget;
}
