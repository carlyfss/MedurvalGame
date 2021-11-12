// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/InventoryComponent.h"
#include "Items/_Base/BaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/_Base/BaseInventoryWidget.h"

// Sets default values
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

#pragma region InventoryInteractions
/** Checks if a given index is empty or not */
bool UInventoryComponent::IsSlotEmpty(const int32 Index) const
{
	return Slots[Index].ItemData.IsNull();
}

/** Get item information at the given Index, if it doesn't find, it returns a nullptr, and the bIsSlotEmpty = true */
TSoftObjectPtr<UBaseItemDA> UInventoryComponent::GetItemInfoAtIndex(const int32 Index, bool& bIsSlotEmpty, uint8& Amount) const
{
	check(Slots.Num() > Index)

	const FInventorySlot* Slot = &Slots[Index];

	if (Slot->ItemData.IsValid())
	{
		TSoftObjectPtr<UBaseItemDA> ItemInfo = Slot->ItemData;

		Amount = Slot->Amount;

		bIsSlotEmpty = false;

		return ItemInfo;
	}

	bIsSlotEmpty = true;

	return nullptr;
}

int UInventoryComponent::GetAmountAtIndex(const int32 Index) const
{
	check(Slots.Num() > Index)

	return Slots[Index].Amount;
}

void UInventoryComponent::SetSlotAmount(const uint8 AmountOfSlots)
{
	SlotAmount = FMath::Clamp(static_cast<int32>(AmountOfSlots), 1, 1000);
}

void UInventoryComponent::SetMaxStackSize(const uint8 StackSize)
{
	MaxStackSize = FMath::Clamp(static_cast<int32>(StackSize), 1, 1000);
}

/** Searches for a empty slot, and if it finds, store the index in the parameter &Index */
bool UInventoryComponent::SearchEmptySlot(int32& Index)
{
	bool bEmptySlot = false;
	int FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (!Slots[i].ItemData.IsValid())
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
bool UInventoryComponent::SearchFreeStack(const TSoftObjectPtr<UBaseItemDA> ItemData, int32& Index)
{
	bool bAvaiableSlot = false;
	int FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (Slots[i].ItemData.IsValid())
			{
				if (Slots[i].ItemData == ItemData && Slots[i].Amount < MaxStackSize)
				{
					bAvaiableSlot = true;
					FoundIndex = i;

					break;
				}
			}
		}
	}

	Index = FoundIndex;
	
	return bAvaiableSlot;
}

bool UInventoryComponent::AddUnstackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, const uint8 Amount, uint8& Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	int FoundIndex = 0;

	if (SearchEmptySlot(FoundIndex))
	{
		Slots[FoundIndex].ItemData = ItemData;
		Slots[FoundIndex].Amount = 1;

		UpdateSlotAtIndex(FoundIndex);
		
		if (Amount > 1)
		{
			const int NewAmount = Amount - 1;

			return AddItem(ItemData, NewAmount, Rest);
		}

		Rest = 0;
		return true;
	}

	Rest = Amount;
	return false;
}

bool UInventoryComponent::AddStackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, const uint8 Amount, uint8& Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	int FoundIndex = 0;

	if (!SearchFreeStack(ItemData, FoundIndex))
	{
		if (SearchEmptySlot(FoundIndex))
		{
			if (Amount > MaxStackSize)
			{
				Slots[FoundIndex].ItemData = ItemData;
				Slots[FoundIndex].Amount = MaxStackSize;

				UpdateSlotAtIndex(FoundIndex);

				const int NewAmount = Amount - MaxStackSize;

				return AddItem(ItemData, NewAmount, Rest);
			}
			
			Slots[FoundIndex].ItemData = ItemData;
			Slots[FoundIndex].Amount = Amount;

			UpdateSlotAtIndex(FoundIndex);

			Rest = 0;

			return true;
		}

		Rest = Amount;
		return false;
	}

	const int CurrentStackAmount = Slots[FoundIndex].Amount + Amount;

	if (CurrentStackAmount > MaxStackSize)
	{
		Slots[FoundIndex].ItemData = ItemData;
		Slots[FoundIndex].Amount = MaxStackSize;

		UpdateSlotAtIndex(FoundIndex);

		const int RestAmount = CurrentStackAmount - MaxStackSize;

		return AddItem(ItemData, RestAmount, Rest);
	}

	Slots[FoundIndex].ItemData = ItemData;
	Slots[FoundIndex].Amount = CurrentStackAmount;

	UpdateSlotAtIndex(FoundIndex);

	return true;
}

TArray<FInventorySlot> UInventoryComponent::GetInventorySlots() const
{
	return Slots;
}

uint8 UInventoryComponent::GetSlotsPerRow() const
{
	return SlotPerRow;
}

uint8 UInventoryComponent::GetSlotAmount() const
{
	return SlotAmount;
}

void UInventoryComponent::SetInventoryWidget(UBaseInventoryWidget* InventoryWidgetRef)
{
	InventoryWidget = InventoryWidgetRef;
}

UBaseInventoryWidget* UInventoryComponent::GetInventoryWidget() const
{
	return InventoryWidget;
}

bool UInventoryComponent::AddItem(TSoftObjectPtr<UBaseItemDA> ItemData, const uint8 Amount, uint8& Rest)
{
	if (ItemData.IsValid())
	{
		if (!ItemData->bCanBeStacked)
		{
			return AddUnstackableItem(ItemData, Amount, Rest);
		}

		return AddStackableItem(ItemData, Amount, Rest);
	}

	return false;
}
#pragma endregion InventoryInteractions