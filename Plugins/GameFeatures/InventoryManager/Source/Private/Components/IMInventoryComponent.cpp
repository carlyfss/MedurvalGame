// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Components/IMInventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "GameFramework/Character.h"
#include "Items/_Base/IMBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Macros/PrintString.h"
#include "UI/_Base/IMInventorySlotWidget.h"
#include "UI/_Base/IMInventoryWidget.h"

#pragma region InventoryInteractions
/** Checks if a given index is empty or not */
bool UIMInventoryComponent::IsSlotEmpty(const int32 Index) const
{
	return Slots[Index].Item.IsNull();
}

/** Get item information at the given Index, if it doesn't find, it returns a nullptr, and the bIsSlotEmpty = true */
UIMBaseItemDA *UIMInventoryComponent::GetItemInfoAtIndex(
		const int32 Index, bool &bIsSlotEmpty, uint8 &Amount) const
{
	check(Slots.Num() > Index);

	const FIMInventorySlot Slot = Slots[Index];

	if (IsValid(Slot.Item))
	{
		UIMBaseItemDA *ItemInfo = Slot.Item;

		Amount = Slot.Amount;

		bIsSlotEmpty = false;

		return ItemInfo;
	}

	bIsSlotEmpty = true;

	return nullptr;
}

int UIMInventoryComponent::GetAmountAtIndex(const int32 Index) const
{
	check(Slots.Num() > Index)

			return Slots[Index]
					.Amount;
}

void UIMInventoryComponent::ToggleInventory()
{
	if (bIsVisible)
	{
		HideInventory();
	}

	ShowInventory();
}

void UIMInventoryComponent::OnRegister()
{
	Super::OnRegister();

	PlayerCharacter = Cast<ACharacter>(GetOwner());

	if (IsValid(PlayerCharacter))
	{
		if (IsValid(PlayerCharacter->InputComponent))
		{
			EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerCharacter->InputComponent);

			if (IsValid(EnhancedInputComponent))
			{
				if (ToggleInventoryAction != nullptr)
				{
					ToggleInventoryBindingHandle = EnhancedInputComponent->BindAction(
																																	 ToggleInventoryAction, ETriggerEvent::Triggered, this,
																																	 &UIMInventoryComponent::OnToggleInventory)
																						 .GetHandle();
				}
			}
		}
	}
}

void UIMInventoryComponent::OnUnregister()
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

/** Searches for a empty slot, and if it finds, store the index in the parameter &Index */
bool UIMInventoryComponent::SearchEmptySlot(int32 &Index)
{
	bool bEmptySlot = false;
	int FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (!Slots[i].Item)
			{
				bEmptySlot = true;
				FoundIndex = i;

				break;
			}
		}
	}
	else
	{
		bEmptySlot = true;
	}

	Index = FoundIndex;
	return bEmptySlot;
}

/** Searches for a empty slot, and if it finds, check the MaxStackSize of the slot and stores the index in the parameter &Index
 * and if the stack is full it return false
 */
bool UIMInventoryComponent::SearchFreeStack(UIMBaseItemDA *Item, int32 &Index)
{
	bool bSlotAvaiable = false;
	int FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (!Slots[i].Item.IsNull())
			{
				if (Slots[i].Item == Item)
				{
					if (Slots[i].Amount < MaxStackSize)
					{
						bSlotAvaiable = true;
						FoundIndex = i;

						break;
					}
				}
			}
		}
	}

	Index = FoundIndex;

	return bSlotAvaiable;
}

bool UIMInventoryComponent::AddUnstackableItem(UIMBaseItemDA *Item, const uint8 Amount,
																							 uint8 &Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	int FoundIndex = 0;

	if (SearchEmptySlot(FoundIndex))
	{
		Slots[FoundIndex].Item = Item;
		Slots[FoundIndex].Amount = 1;

		OnUpdateSlotAtIndex.Broadcast(FoundIndex);

		if (Amount > 1)
		{
			const int NewAmount = Amount - 1;

			return AddItem(Item, NewAmount, Rest);
		}

		Rest = 0;
		return true;
	}

	Rest = Amount;
	return false;
}

bool UIMInventoryComponent::AddStackableItem(UIMBaseItemDA *Item, const uint8 Amount, uint8 &Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	int FoundIndex = 0;

	if (!SearchFreeStack(Item, FoundIndex))
	{
		if (SearchEmptySlot(FoundIndex))
		{
			if (Amount > MaxStackSize)
			{
				Slots[FoundIndex].Item = Item;
				Slots[FoundIndex].Amount = MaxStackSize;

				OnUpdateSlotAtIndex.Broadcast(FoundIndex);

				const int NewAmount = Amount - MaxStackSize;

				return AddItem(Item, NewAmount, Rest);
			}

			Slots[FoundIndex].Item = Item;
			Slots[FoundIndex].Amount = Amount;

			OnUpdateSlotAtIndex.Broadcast(FoundIndex);

			Rest = 0;

			return true;
		}

		Rest = Amount;
		return false;
	}

	const int CurrentStackAmount = Slots[FoundIndex].Amount + Amount;

	if (CurrentStackAmount > MaxStackSize)
	{
		Slots[FoundIndex].Item = Item;
		Slots[FoundIndex].Amount = MaxStackSize;

		OnUpdateSlotAtIndex.Broadcast(FoundIndex);

		const int RestAmount = CurrentStackAmount - MaxStackSize;

		return AddItem(Item, RestAmount, Rest);
	}

	Slots[FoundIndex].Item = Item;
	Slots[FoundIndex].Amount = CurrentStackAmount;

	OnUpdateSlotAtIndex.Broadcast(FoundIndex);

	return true;
}

bool UIMInventoryComponent::RemoveItemAtIndex(const int32 Index, const uint8 Amount)
{
	if (!IsSlotEmpty(Index) && Amount > 0)
	{
		FScopeLock Lock(&SocketsCriticalSection);

		if (Amount >= GetAmountAtIndex(Index))
		{
			TArray<UIMInventorySlotWidget *> SlotWidgets = InventoryWidget->GetSlotWidgets();
			UIMInventorySlotWidget *SlotWidget = SlotWidgets[Index];

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

bool UIMInventoryComponent::SwapSlots(const int32 OriginIndex, const int32 TargetIndex)
{
	FScopeLock Lock(&SocketsCriticalSection);

	const int32 SlotsLastIndex = Slots.Num() - 1;

	if (OriginIndex > SlotsLastIndex || TargetIndex > SlotsLastIndex)
	{
		return false;
	}

	const FIMInventorySlot TempSlot = Slots[TargetIndex];

	Slots[TargetIndex].Item = Slots[OriginIndex].Item;
	Slots[TargetIndex].Amount = Slots[OriginIndex].Amount;

	Slots[OriginIndex].Item = TempSlot.Item;
	Slots[OriginIndex].Amount = TempSlot.Amount;

	OnUpdateSlotAtIndex.Broadcast(OriginIndex);
	OnUpdateSlotAtIndex.Broadcast(TargetIndex);

	return true;
}

bool UIMInventoryComponent::SplitStack(const int32 Index)
{
	if (IsSlotEmpty(Index))
	{
		return false;
	}

	bool bIsSlotEmpty = false;
	uint8 CurrentAmount = 0;
	UIMBaseItemDA *ItemInfo = GetItemInfoAtIndex(Index, bIsSlotEmpty, CurrentAmount);

	if (!ItemInfo)
		return false;

	if (!ItemInfo->bCanBeStacked && CurrentAmount <= 1)
		return false;

	int32 FoundSlotIndex = 0;
	const uint8 HalfAmount = (CurrentAmount / 2);

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

bool UIMInventoryComponent::SplitStackToIndex(const int32 SourceIndex, const int32 TargetIndex, uint8 Amount)
{
	bool bIsSlotEmpty;
	uint8 AmountAtSlot;

	UIMBaseItemDA *ItemAtSourceSlot = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);

	const bool bTargetSlotHasAmount = AmountAtSlot > 1;
	const bool bIsAmountLessThanTargetAmount = AmountAtSlot > Amount;

	if (IsSlotEmpty(TargetIndex) && !IsSlotEmpty(SourceIndex) && ItemAtSourceSlot->bCanBeStacked &&
			bTargetSlotHasAmount && bIsAmountLessThanTargetAmount)
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

TArray<FIMInventorySlot> UIMInventoryComponent::GetInventorySlots() const
{
	return Slots;
}

uint8 UIMInventoryComponent::GetSlotsPerRow() const
{
	return SlotPerRow;
}

uint8 UIMInventoryComponent::GetSlotAmount() const
{
	return SlotAmount;
}

void UIMInventoryComponent::SetInventoryWidget(UIMInventoryWidget *InventoryWidgetRef)
{
	InventoryWidget = InventoryWidgetRef;
}

void UIMInventoryComponent::SetIsVisible(bool bIsInventoryVisible)
{
	bIsVisible = bIsInventoryVisible;
}

bool UIMInventoryComponent::GetIsVisible() const
{
	return bIsVisible;
}

UIMInventoryWidget *UIMInventoryComponent::GetInventoryWidget() const
{
	return InventoryWidget;
}

bool UIMInventoryComponent::AddItem(UIMBaseItemDA *Item, uint8 Amount, uint8 &Rest)
{
	if (Item)
	{
		if (!Item->bCanBeStacked)
		{
			OnItemAdded.Broadcast(Item, Amount);
			return AddUnstackableItem(Item, Amount, Rest);
		}

		OnItemAdded.Broadcast(Item, Amount);
		return AddStackableItem(Item, Amount, Rest);
	}

	return false;
}

bool UIMInventoryComponent::AddToIndex(uint8 SourceIndex, uint8 TargetIndex)
{
	const UClass *SourceSlotClass = Slots[SourceIndex].Item->GetClass();

	if (Slots[TargetIndex].Item != nullptr)
	{
		const UClass *TargetSlotClass = Slots[TargetIndex].Item->GetClass();

		const bool bIsClassEqual = SourceSlotClass == TargetSlotClass;

		const bool bIsTargetLessThanMaxSize = Slots[TargetIndex].Amount < MaxStackSize;

		bool bIsSlotEmpty;
		uint8 AmountAtSlot;
		const TSoftObjectPtr<UIMBaseItemDA> SourceItem = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);

		if (!bIsClassEqual && !bIsTargetLessThanMaxSize && !SourceItem->bCanBeStacked)
		{
			return false;
		}
	}

	const uint8 TargetTotalRestAmount = MaxStackSize - GetAmountAtIndex(TargetIndex);
	const uint8 SourceAmount = GetAmountAtIndex(SourceIndex);

	if (TargetTotalRestAmount <= SourceAmount)
	{
		const uint8 SourceRestAmount = GetAmountAtIndex(SourceIndex) - (MaxStackSize - GetAmountAtIndex(TargetIndex));

		Slots[SourceIndex].Amount = SourceRestAmount;

		Slots[TargetIndex].Item = Slots[SourceIndex].Item;
		Slots[TargetIndex].Amount = MaxStackSize;
	}
	else
	{
		const uint8 NewTotalAmount = GetAmountAtIndex(SourceIndex) + GetAmountAtIndex(TargetIndex);

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

bool UIMInventoryComponent::OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd)
{
	UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager)
		return false;

	ItemIdToAddInv = ItemIdToAdd;

	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);

	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UIMInventoryComponent::AfterLoad);

	AssetManager->LoadPrimaryAsset(ItemIdToAdd, BundlesToLoad, Delegate);

	return true;
}

void UIMInventoryComponent::AfterLoad()
{
	UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager)
		return;

	UIMBaseItemDA *Item = Cast<UIMBaseItemDA>(AssetManager->GetPrimaryAssetObject(ItemIdToAddInv));

	if (Item)
	{
		uint8 Rest = 0;

		AddItem(Item, 1, Rest);
	}
}

void UIMInventoryComponent::UpdateSlotAfterLoad_Implementation(uint8 SlotIndex)
{
	TArray<UIMInventorySlotWidget *> SlotWidgets = InventoryWidget->GetSlotWidgets();
	UIMInventorySlotWidget *SlotWidget = SlotWidgets[SlotIndex];

	SlotWidget->UpdateSlot();
}
