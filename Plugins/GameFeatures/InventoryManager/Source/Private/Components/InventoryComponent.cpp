// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/InventoryComponent.h"
#include "GameFramework/Character.h"
#include "Items/BaseItemDA.h"

// Sets default values
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Owner = Cast<ACharacter>(GetOwner());

	SetPlayerReference(Owner);

	Slots.Reserve(AmountOfSlots);
}

/** Checks if a given index is empty or not */
bool UInventoryComponent::IsSlotEmpty(const int Index) const
{
	return !Slots[Index].ItemData.IsValid();
}

/** Get item information at the given Index, if it doesn't find, it returns a nullptr, and the bIsSlotEmpty = true */
TSoftObjectPtr<UBaseItemDA> UInventoryComponent::GetItemInfoAtIndex(const int Index, bool& bIsSlotEmpty, int& Amount) const
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

int UInventoryComponent::GetAmountAtIndex(const int Index) const
{
	check(Slots.Num() > Index)

	return Slots[Index].Amount;
}

/** Searches for a empty slot, and if it finds, store the index in the parameter &Index */
bool UInventoryComponent::SearchEmptySlot(int& Index)
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
bool UInventoryComponent::SearchFreeStack(const TSoftObjectPtr<UBaseItemDA> ItemData, int& Index)
{
	bool bEmptySlot = false;
	int FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			FInventorySlot Slot = Slots[i];

			if (Slot.ItemData.IsValid())
			{
				if (Slot.ItemData == ItemData && Slot.Amount < MaxStackSize)
				{
					bEmptySlot = true;
					FoundIndex = i;

					break;
				}
			}
		}
	}

	Index = FoundIndex;
	return bEmptySlot;
}

bool UInventoryComponent::AddUnstackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, const int Amount, int& Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	int FoundIndex = 0;

	if (SearchEmptySlot(FoundIndex))
	{
		FInventorySlot* TemporaryData = new FInventorySlot();
		FoundIndex = Slots.Add(*TemporaryData);

		Slots[FoundIndex].ItemData = ItemData;
		Slots[FoundIndex].Amount = 1;

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

bool UInventoryComponent::AddStackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, const int Amount, int& Rest)
{
	FScopeLock Lock(&SocketsCriticalSection);

	int FoundIndex = 0;

	if (!SearchFreeStack(ItemData, FoundIndex))
	{
		if (SearchEmptySlot(FoundIndex))
		{
			if (Amount > MaxStackSize)
			{
				FInventorySlot* TemporaryData = new FInventorySlot();
				FoundIndex = Slots.Add(*TemporaryData);

				Slots[FoundIndex].ItemData = ItemData;
				Slots[FoundIndex].Amount = MaxStackSize;

				const int NewAmount = Amount - MaxStackSize;

				return AddItem(ItemData, NewAmount, Rest);
			}

			FInventorySlot* TemporaryData = new FInventorySlot();
			FoundIndex = Slots.Add(*TemporaryData);

			Slots[FoundIndex].ItemData = ItemData;
			Slots[FoundIndex].Amount = Amount;

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

		const int RestAmount = CurrentStackAmount - MaxStackSize;

		return AddItem(ItemData, RestAmount, Rest);
	}

	Slots[FoundIndex].ItemData = ItemData;
	Slots[FoundIndex].Amount = CurrentStackAmount;

	return true;
}

void UInventoryComponent::SetPlayerReference(ACharacter* PlayerRef)
{
	PlayerReference = PlayerRef;
}

bool UInventoryComponent::AddItem(TSoftObjectPtr<UBaseItemDA> ItemData, const int Amount, int& Rest)
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
