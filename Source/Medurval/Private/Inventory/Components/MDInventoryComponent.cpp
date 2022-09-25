// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Components/MDInventoryComponent.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Inventory/Widgets/MDInventorySlotWidget.h"
#include "Inventory/Widgets/MDInventoryWidget.h"

void UMDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMDPlayerCharacter>(GetOwner());

	Slots.SetNum(SlotAmount);
	EquipmentSlots.SetNum(EquipmentSlotsAmount);
	WeaponSlots.SetNum(WeaponSlotsAmount);
}

/** Checks if a given index is empty or not */
bool UMDInventoryComponent::IsSlotEmpty(uint8 Index) const
{
	return !Slots[Index].Item || Slots[Index].Amount == 0;
}

/** Get item information at the given Index, if it doesn't find, it returns a
 * nullptr, and the bIsSlotEmpty = true */
UMDItemDataAsset* UMDInventoryComponent::GetItemInfoAtIndex(uint8 Index, bool& bIsSlotEmpty, uint8& Amount) const
{
	check(Slots.Num() > Index);

	const FMDInventorySlot Slot = Slots[Index];

	if (IsValid(Slot.Item))
	{
		UMDItemDataAsset* ItemInfo = Slot.Item;
		Amount = Slot.Amount;
		bIsSlotEmpty = false;

		return ItemInfo;
	}

	bIsSlotEmpty = true;
	return nullptr;
}

uint8 UMDInventoryComponent::GetAmountAtIndex(uint8 Index) const
{
	check(Slots.Num() > Index)
	return Slots[Index].Amount;
}

TArray<FMDInventorySlot> UMDInventoryComponent::GetSlots() const
{
	return Slots;
}

/** Searches for a empty slot, and if it finds, store the index in the parameter
 * &Index */
bool UMDInventoryComponent::SearchEmptySlot(uint8& Index)
{
	bool bEmptySlot = false;
	uint8 FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].Item || Slots[i].Amount > 0)
			{
				continue;
			}

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
bool UMDInventoryComponent::SearchFreeStack(UMDItemDataAsset* Item, uint8& Index)
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

bool UMDInventoryComponent::AddItem(UMDItemDataAsset* Item, uint8 Amount, uint8& Rest)
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

bool UMDInventoryComponent::AddUnstackableItem(UMDItemDataAsset* Item, uint8 Amount, uint8& Rest)
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

bool UMDInventoryComponent::AddStackableItem(UMDItemDataAsset* Item, uint8 Amount, uint8& Rest)
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
		}
		else
		{
			Slots[FoundIndex].Item = Item;
			Slots[FoundIndex].Amount = CurrentStackAmount;
			bAddedSuccessfully = true;
		}
	}

	OnUpdateSlotAtIndex.Broadcast(FoundIndex);
	return bAddedSuccessfully;
}

bool UMDInventoryComponent::RemoveItemAtIndex(uint8 Index, uint8 Amount)
{
	bool bIsItemRemoved = false;

	if (!IsSlotEmpty(Index) && Amount > 0)
	{
		FScopeLock Lock(&SocketsCriticalSection);

		if (Amount >= GetAmountAtIndex(Index))
		{
			Slots[Index].Item = nullptr;
			Slots[Index].Amount = 0;

			OnItemRemoved.Broadcast(Slots[Index].Item, Slots[Index].Amount, Index);
			bIsItemRemoved = true;
		}
		else
		{
			Slots[Index].Amount -= Amount;

			OnItemRemoved.Broadcast(Slots[Index].Item, Slots[Index].Amount, Index);
			OnUpdateSlotAtIndex.Broadcast(Index);

			bIsItemRemoved = true;
		}
	}

	return bIsItemRemoved;
}

bool UMDInventoryComponent::SwapSlots(uint8 OriginIndex, uint8 TargetIndex)
{
	FScopeLock Lock(&SocketsCriticalSection);

	const uint8 SlotsLastIndex = Slots.Num() - 1;

	if (OriginIndex > SlotsLastIndex || TargetIndex > SlotsLastIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Origin or Target Index is higher than maximum slots."));
		return false;
	}

	const FMDInventorySlot TemporarySlot = Slots[TargetIndex];

	Slots[TargetIndex].Item = Slots[OriginIndex].Item;
	Slots[TargetIndex].Amount = Slots[OriginIndex].Amount;

	Slots[OriginIndex].Item = TemporarySlot.Item;
	Slots[OriginIndex].Amount = TemporarySlot.Amount;

	OnUpdateSlotAtIndex.Broadcast(OriginIndex);
	OnUpdateSlotAtIndex.Broadcast(TargetIndex);

	return true;
}

bool UMDInventoryComponent::SplitStack(uint8 Index)
{
	bool bHasSplitTheStack = false;
	bool bIsSlotEmpty = false;
	uint8 CurrentAmount = 0;

	if (!IsSlotEmpty(Index))
	{
		UMDItemDataAsset* ItemInfo = GetItemInfoAtIndex(Index, bIsSlotEmpty, CurrentAmount);

		if (ItemInfo && ItemInfo->bCanBeStacked && CurrentAmount > 1)
		{
			uint8 FoundSlotIndex = 0;
			uint8 HalfAmount = (CurrentAmount / 2);

			if (SearchEmptySlot(FoundSlotIndex))
			{
				FScopeLock Lock(&SocketsCriticalSection);

				Slots[Index].Item = ItemInfo;
				Slots[Index].Amount = CurrentAmount - HalfAmount;

				Slots[FoundSlotIndex].Item = ItemInfo;
				Slots[FoundSlotIndex].Amount = HalfAmount;

				OnUpdateSlotAtIndex.Broadcast(Index);
				OnUpdateSlotAtIndex.Broadcast(FoundSlotIndex);
				bHasSplitTheStack = true;
			}
		}
	}

	return bHasSplitTheStack;
}

bool UMDInventoryComponent::SplitStackToIndex(uint8 SourceIndex, uint8 TargetIndex, uint8 Amount)
{
	bool bIsSlotEmpty;
	uint8 AmountAtSlot;

	UMDItemDataAsset* ItemAtSourceSlot = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);

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

bool UMDInventoryComponent::LoadAndAddItem(FPrimaryAssetId TargetItemId, uint8 Amount)
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager)
		return false;

	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);

	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(
		this, &UMDInventoryComponent::AddItemOnLoadCompleted, TargetItemId, Amount);

	AssetManager->LoadPrimaryAsset(TargetItemId, BundlesToLoad, Delegate);
	return true;
}

bool UMDInventoryComponent::OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd, uint8 Amount)
{
	return LoadAndAddItem(ItemIdToAdd, Amount);
}

void UMDInventoryComponent::AddItemOnLoadCompleted(FPrimaryAssetId TargetItemId, uint8 Amount)
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager)
		return;

	UMDItemDataAsset* Item = Cast<UMDItemDataAsset>(AssetManager->GetPrimaryAssetObject(TargetItemId));

	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemID %s was not loaded yet!"), *TargetItemId.ToString());
		return;
	}

	uint8 Rest = 0;
	AddItem(Item, Amount, Rest);
}

bool UMDInventoryComponent::AddToIndex(uint8 SourceIndex, uint8 TargetIndex)
{
	const UClass* SourceSlotClass = Slots[SourceIndex].Item->GetClass();

	if (Slots[TargetIndex].Item)
	{
		const UClass* TargetSlotClass = Slots[TargetIndex].Item->GetClass();

		bool bIsClassEqual = SourceSlotClass == TargetSlotClass;
		bool bIsTargetLessThanMaxSize = Slots[TargetIndex].Amount < MaxStackSize;
		bool bIsSlotEmpty;

		uint8 AmountAtSlot;

		const UMDItemDataAsset* SourceItem = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);

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

void UMDInventoryComponent::UpdateSlotAfterLoad_Implementation(uint8 SlotIndex)
{
	OnUpdateSlotAtIndex.Broadcast(SlotIndex);
}

bool UMDInventoryComponent::RemoveItemFromInventory_Implementation(FPrimaryAssetId ItemIdToRemove, uint8 Amount,
                                                                   int& Rest)
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager)
		return false;

	bool bHasRemovedItem = false;
	Rest = 0;
	int CurrentAmount = Amount;

	UMDItemDataAsset* Item = Cast<UMDItemDataAsset>(AssetManager->GetPrimaryAssetObject(ItemIdToRemove));

	for (int i = Slots.Num() - 1; i >= 0; i--)
	{
		FMDInventorySlot Slot = Slots[i];

		if (Slot.Item && Slot.Item == Item)
		{
			if (Amount <= Slot.Amount)
			{
				RemoveItemAtIndex(i, CurrentAmount);
				CurrentAmount = 0;
				bHasRemovedItem = true;
				break;
			}

			RemoveItemAtIndex(i, Slot.Amount);
			CurrentAmount -= Slot.Amount;
			break;
		}
	}

	Rest = CurrentAmount;
	return bHasRemovedItem;
}
