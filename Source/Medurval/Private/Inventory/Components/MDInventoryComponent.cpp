// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Components/MDInventoryComponent.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Items/MDEquipmentDataAsset.h"
#include "Inventory/Items/MDItemDataAsset.h"

void UMDInventoryComponent::InitializeSlotArrays()
{
	Slots.SetNum(SlotAmount);
	EquipmentSlots.SetNum(EquipmentSlotsAmount);
	AccessorySlots.SetNum(AccessorySlotsAmount);
	WeaponSlots.SetNum(WeaponSlotsAmount);

	for (int i = 0; i < Slots.Num(); i++)
	{
		Slots[i] = FMDInventorySlot();
	}

	for (int i = 0; i < EquipmentSlots.Num(); i++)
	{
		EquipmentSlots[i] = FMDInventoryEquipmentSlot();
	}

	for (int i = 0; i < AccessorySlots.Num(); i++)
	{
		AccessorySlots[i] = FMDInventoryAccessorySlot();
	}

	for (int i = 0; i < WeaponSlots.Num(); i++)
	{
		WeaponSlots[i] = FMDInventoryWeaponSlot();
	}

	SetupEquipmentSlots();
	SetupAccessorySlots();
	SetupWeaponSlots();
}

void UMDInventoryComponent::SetupEquipmentSlots()
{
	EquipmentSlots[0].Attachment = EMDEquipmentAttachment::Helmet;
	EquipmentSlots[1].Attachment = EMDEquipmentAttachment::Chest;
	EquipmentSlots[2].Attachment = EMDEquipmentAttachment::Gloves;
	EquipmentSlots[3].Attachment = EMDEquipmentAttachment::Pants;
	EquipmentSlots[4].Attachment = EMDEquipmentAttachment::Boots;
}

void UMDInventoryComponent::SetupAccessorySlots()
{
	AccessorySlots[0].Attachment = EMDAccessoryAttachment::Shoulder;
	AccessorySlots[1].Attachment = EMDAccessoryAttachment::Necklace;
	AccessorySlots[2].Attachment = EMDAccessoryAttachment::Ring;
	AccessorySlots[3].Attachment = EMDAccessoryAttachment::Belt;
	AccessorySlots[4].Attachment = EMDAccessoryAttachment::Gem;
}

void UMDInventoryComponent::SetupWeaponSlots()
{
	WeaponSlots[0].Attachment = EMDWeaponAttachment::Primary;
	WeaponSlots[1].Attachment = EMDWeaponAttachment::Secondary;
	WeaponSlots[2].Attachment = EMDWeaponAttachment::Ammo;
}

void UMDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMDPlayerCharacter>(GetOwner());

	InitializeSlotArrays();
}

/** Checks if a given index is empty or not */
bool UMDInventoryComponent::IsSlotEmpty(int32 Index) const
{
	return !Slots[Index].IsValid();
}

/** Get item information at the given Index, if it doesn't find, it returns a
 * nullptr, and the bIsSlotEmpty = true */
FPrimaryAssetId UMDInventoryComponent::GetItemInfoAtIndex(int32 Index, bool& bIsSlotEmpty, int32& Amount) const
{
	check(Slots.Num() > Index);

	const FMDInventorySlot Slot = Slots[Index];

	if (Slot.Item.IsValid())
	{
		Amount = Slot.Amount;
		bIsSlotEmpty = false;

		return Slot.Item;
	}

	bIsSlotEmpty = true;
	return FPrimaryAssetId();
}

int32 UMDInventoryComponent::GetAmountAtIndex(int32 Index) const
{
	check(Slots.Num() > Index)
	return Slots[Index].Amount;
}

TArray<FMDInventorySlot> UMDInventoryComponent::GetSlots() const
{
	return Slots;
}

TArray<FMDInventoryEquipmentSlot> UMDInventoryComponent::GetEquipmentSlots() const
{
	return EquipmentSlots;
}

TArray<FMDInventoryAccessorySlot> UMDInventoryComponent::GetAccessorySlots() const
{
	return AccessorySlots;
}

TArray<FMDInventoryWeaponSlot> UMDInventoryComponent::GetWeaponSlots() const
{
	return WeaponSlots;
}

void UMDInventoryComponent::EquipItem(EMDEquipmentAttachment Attachment, FPrimaryAssetId ItemId)
{
	UMDEquipmentDataAsset* Equipment = GetMDGameInstance()->GetCastPrimaryAssetId<UMDEquipmentDataAsset>(ItemId);

	if (Equipment)
	{
		bool bHasFound;
		int32 SlotIndex = FindSlotIndexByAttachment(Attachment, bHasFound);

		if (bHasFound)
		{
			EquipmentSlots[SlotIndex].Item = ItemId;
			EquipmentSlots[SlotIndex].Amount = 1;

			PlayerCharacter->EquipItem(Attachment, ItemId);
			OnItemEquipped.Broadcast(ItemId, Attachment);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."));
		}
			
	}
}

void UMDInventoryComponent::UnequipItem(EMDEquipmentAttachment Attachment)
{
	bool bHasFound;
	const int32 SlotIndex = FindSlotIndexByAttachment(Attachment, bHasFound);

	if (bHasFound)
	{
		int32 Rest;
		AddItem(EquipmentSlots[SlotIndex].Item, 1, Rest);
		EquipmentSlots[SlotIndex].Item = FPrimaryAssetId();
		EquipmentSlots[SlotIndex].Amount = 0;

		PlayerCharacter->UnequipItem(Attachment);
		OnItemUnequipped.Broadcast(Attachment);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."));
	}
}


int32 UMDInventoryComponent::FindSlotIndexByAttachment(EMDEquipmentAttachment Attachment, bool& bHasFound) const
{
	bHasFound = false;
	int32 FoundSlotIndex = -1;

	for (int i = 0; i < EquipmentSlots.Num(); i++)
	{
		if (EquipmentSlots[i].Attachment == Attachment)
		{
			FoundSlotIndex = i;
			bHasFound = true;
			break;
		}
	}

	return FoundSlotIndex;
}

bool UMDInventoryComponent::IsSlotEmptyAtAttachment(EMDEquipmentAttachment Attachment) const
{
	bool IsIndexValid;
	int32 SlotIndex = FindSlotIndexByAttachment(Attachment, IsIndexValid);
	bool IsEmpty = true;

	if (IsIndexValid && EquipmentSlots[SlotIndex].IsValid())
	{
		IsEmpty = false;
	}

	return IsEmpty;
}

/** Searches for a empty slot, and if it finds, store the index in the parameter
 * &Index */
bool UMDInventoryComponent::SearchEmptySlot(int32& Index)
{
	bool bEmptySlot = false;
	int32 FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].IsValid())
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
bool UMDInventoryComponent::SearchFreeStack(FPrimaryAssetId Item, int32& Index)
{
	bool bSlotAvailable = false;
	int32 FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].IsValid() && !Slots[i].IsSameItem(Item))
				continue;
			if (Slots[i].IsFull())
				continue;

			bSlotAvailable = true;
			FoundIndex = i;
			break;
		}
	}

	Index = FoundIndex;

	return bSlotAvailable;
}

bool UMDInventoryComponent::AddItem(FPrimaryAssetId Item, int32 Amount, int32& Rest)
{
	if (!Item.IsValid())
		return false;

	UMDItemDataAsset* ItemInfo = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(Item);

	if (ItemInfo && !ItemInfo->bCanBeStacked)
	{
		return AddUnstackableItem(Item, Amount, Rest);
	}

	
	return AddStackableItem(Item, Amount, Rest);
}

bool UMDInventoryComponent::AddUnstackableItem(FPrimaryAssetId Item, int32 Amount, int32& Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	bool bAddedSuccessfully = false;
	int32 FoundIndex = 0;

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
			const int32 NewAmount = Amount - 1;
			bAddedSuccessfully = AddItem(Item, NewAmount, Rest);
		}

		Rest = 0;
	}

	OnItemAdded.Broadcast(Item, Amount);
	OnUpdateSlotAtIndex.Broadcast(FoundIndex);
	return bAddedSuccessfully;
}

bool UMDInventoryComponent::AddStackableItem(FPrimaryAssetId Item, int32 Amount, int32& Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	bool bAddedSuccessfully = false;
	int32 AmountRest = 0;
	int32 FoundIndex = 0;

	if (!SearchFreeStack(Item, FoundIndex))
	{
		// Add to empty slot
		if (SearchEmptySlot(FoundIndex))
		{
			if (Amount > FMDInventorySlot::MAX_SlotAmount)
			{
				Slots[FoundIndex].Item = Item;

				const int32 RestAmount = Slots[FoundIndex].AddAmount(Amount);
				bAddedSuccessfully = AddItem(Item, RestAmount, AmountRest);
			}
			else
			{
				Slots[FoundIndex].Item = Item;
				Slots[FoundIndex].AddAmount(Amount);

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
		const int32 RestAmount = Slots[FoundIndex].AddAmount(Amount);

		if (RestAmount > 0)
		{
			Slots[FoundIndex].Item = Item;
			bAddedSuccessfully = AddItem(Item, RestAmount, AmountRest);
		}
		else
		{
			Slots[FoundIndex].Item = Item;
			bAddedSuccessfully = true;
		}
	}

	OnItemAdded.Broadcast(Item, Amount);
	OnUpdateSlotAtIndex.Broadcast(FoundIndex);
	return bAddedSuccessfully;
}

bool UMDInventoryComponent::RemoveItemAtIndex(int32 Index, int32 Amount)
{
	bool bIsItemRemoved = false;

	if (!IsSlotEmpty(Index) && Amount > 0)
	{
		FScopeLock Lock(&SocketsCriticalSection);

		if (Amount >= GetAmountAtIndex(Index))
		{
			const int32 RemovedAmount = Slots[Index].Amount;
			Slots[Index].Item = FPrimaryAssetId();
			Slots[Index].Amount = 0;

			OnItemRemoved.Broadcast(Slots[Index].Item, RemovedAmount, Index);
			bIsItemRemoved = true;
		}
		else
		{
			Slots[Index].RemoveAmount(Amount);

			OnItemRemoved.Broadcast(Slots[Index].Item, Amount, Index);
			OnUpdateSlotAtIndex.Broadcast(Index);

			bIsItemRemoved = true;
		}
	}

	return bIsItemRemoved;
}

bool UMDInventoryComponent::SwapSlots(int32 OriginIndex, int32 TargetIndex)
{
	FScopeLock Lock(&SocketsCriticalSection);

	const int32 SlotsLastIndex = Slots.Num() - 1;

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

bool UMDInventoryComponent::SplitStack(int32 Index)
{
	bool bHasSplitTheStack = false;
	bool bIsSlotEmpty = false;
	int32 CurrentAmount = 0;

	if (!IsSlotEmpty(Index))
	{
		FPrimaryAssetId ItemId = GetItemInfoAtIndex(Index, bIsSlotEmpty, CurrentAmount);
		UMDItemDataAsset* ItemInfo = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(ItemId);

		if (ItemInfo && ItemInfo->bCanBeStacked && CurrentAmount > 1)
		{
			int32 FoundSlotIndex = 0;
			int32 HalfAmount = (CurrentAmount / 2);

			if (SearchEmptySlot(FoundSlotIndex))
			{
				FScopeLock Lock(&SocketsCriticalSection);

				Slots[Index].Item = ItemId;
				Slots[Index].RemoveAmount(HalfAmount);

				Slots[FoundSlotIndex].Item = ItemId;
				Slots[FoundSlotIndex].AddAmount(HalfAmount);

				OnUpdateSlotAtIndex.Broadcast(Index);
				OnUpdateSlotAtIndex.Broadcast(FoundSlotIndex);
				bHasSplitTheStack = true;
			}
		}
	}

	return bHasSplitTheStack;
}

bool UMDInventoryComponent::SplitStackToIndex(int32 SourceIndex, int32 TargetIndex, int32 Amount)
{
	bool bIsSlotEmpty;
	int32 AmountAtSlot;

	FPrimaryAssetId ItemId = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);
	UMDItemDataAsset* ItemInfo = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(ItemId);

	bool bTargetSlotHasAmount = AmountAtSlot > 1;
	bool bIsAmountLessThanTargetAmount = AmountAtSlot > Amount;

	if (IsSlotEmpty(TargetIndex) && !IsSlotEmpty(SourceIndex) &&
		ItemInfo->bCanBeStacked && bTargetSlotHasAmount &&
		bIsAmountLessThanTargetAmount)
	{
		Slots[SourceIndex].Amount -= Amount;
		Slots[TargetIndex].Item = ItemId;
		Slots[TargetIndex].Amount = Amount;

		OnUpdateSlotAtIndex.Broadcast(SourceIndex);
		OnUpdateSlotAtIndex.Broadcast(TargetIndex);
		return true;
	}

	return false;
}

bool UMDInventoryComponent::OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToAdd, int32 Amount)
{
	int32 Rest = 0;
	return AddItem(ItemIdToAdd, Amount, Rest);
}

void UMDInventoryComponent::AddItemOnLoadCompleted(FPrimaryAssetId TargetItemId, int32 Amount)
{
	int32 Rest = 0;
	AddItem(TargetItemId, Amount, Rest);
}

bool UMDInventoryComponent::AddToIndex(int32 SourceIndex, int32 TargetIndex)
{
	if (Slots[TargetIndex].IsValid())
	{
		const bool bIsClassEqual = Slots[SourceIndex].IsSameItem(Slots[TargetIndex].Item);
		const bool bIsTargetLessThanMaxSize = !Slots[TargetIndex].IsFull();
		bool bIsSlotEmpty;

		int32 AmountAtSlot;

		const FPrimaryAssetId SourceItem = GetItemInfoAtIndex(SourceIndex, bIsSlotEmpty, AmountAtSlot);
		const UMDItemDataAsset* ItemInfo = GetMDGameInstance()->GetCastPrimaryAssetId<UMDItemDataAsset>(SourceItem);

		if (!bIsClassEqual && !bIsTargetLessThanMaxSize && !ItemInfo->bCanBeStacked)
		{
			return false;
		}
	}

	int32 TargetTotalRestAmount = FMDInventorySlot::MAX_SlotAmount - GetAmountAtIndex(TargetIndex);
	int32 SourceAmount = GetAmountAtIndex(SourceIndex);

	if (TargetTotalRestAmount <= SourceAmount)
	{
		Slots[SourceIndex].RemoveAmount(TargetTotalRestAmount);

		Slots[TargetIndex].Item = Slots[SourceIndex].Item;
		Slots[TargetIndex].Amount = FMDInventorySlot::MAX_SlotAmount;
	}
	else
	{
		Slots[TargetIndex].Item = Slots[SourceIndex].Item;
		Slots[TargetIndex].AddAmount(SourceAmount);

		Slots[SourceIndex].Item = FPrimaryAssetId();
		Slots[SourceIndex].Amount = 0;
	}

	OnUpdateSlotAtIndex.Broadcast(SourceIndex);
	OnUpdateSlotAtIndex.Broadcast(TargetIndex);

	return true;
}
#pragma endregion InventoryInteractions

void UMDInventoryComponent::UpdateSlotAfterLoad_Implementation(int32 SlotIndex)
{
	OnUpdateSlotAtIndex.Broadcast(SlotIndex);
}

bool UMDInventoryComponent::RemoveItemFromInventory_Implementation(FPrimaryAssetId ItemIdToRemove, int32 Amount,
                                                                   int& Rest)
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager)
		return false;

	bool bHasRemovedItem = false;
	int CurrentAmount = Amount;
	Rest = 0;

	for (int i = Slots.Num() - 1; i >= 0; i--)
	{
		FMDInventorySlot Slot = Slots[i];

		if (Slot.IsValid() && Slot.IsSameItem(ItemIdToRemove))
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

int32 UMDInventoryComponent::GetSlotsPerRow() const
{
	return SlotsPerRow;
}

int32 UMDInventoryComponent::GetEquipmentSlotsAmount() const
{
	return EquipmentSlotsAmount;
}

int32 UMDInventoryComponent::GetAccessorySlotsAmount() const
{
	return AccessorySlotsAmount;
}

int32 UMDInventoryComponent::GetWeaponSlotsAmount() const
{
	return WeaponSlotsAmount;
}
