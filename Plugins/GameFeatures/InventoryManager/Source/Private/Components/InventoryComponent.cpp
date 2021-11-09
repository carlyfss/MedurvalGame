// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/InventoryComponent.h"
#include "GameFramework/Character.h"
#include "Items/_Base/BaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"

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

	Slots.SetNum(SlotAmount);
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SetPlayerReference(nullptr);
}

/** Checks if a given index is empty or not */
bool UInventoryComponent::IsSlotEmpty(const int32 Index) const
{
	return !Slots[Index].ItemData.IsValid();
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

				const int NewAmount = Amount - MaxStackSize;

				return AddItem(ItemData, NewAmount, Rest);
			}
			
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
