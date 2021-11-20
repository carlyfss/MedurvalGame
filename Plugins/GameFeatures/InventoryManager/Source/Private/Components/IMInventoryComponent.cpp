// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/IMInventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Items/Pìckups/_Base/IMItemPickup.h"
#include "Items/_Base/BaseItemPrimaryDA.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Macros/PrintString.h"
#include "UI/_Base/IMInventoryWidget.h"

// Sets default values
UIMInventoryComponent::UIMInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickInterval = 0.075f;
}

#pragma region InventoryInteractions
/** Checks if a given index is empty or not */
bool UIMInventoryComponent::IsSlotEmpty(const int32 Index) const
{
	return Slots[Index].ItemData.IsNull();
}

/** Get item information at the given Index, if it doesn't find, it returns a nullptr, and the bIsSlotEmpty = true */
TSoftObjectPtr<UBaseItemPrimaryDA> UIMInventoryComponent::GetItemInfoAtIndex(
	const int32 Index, bool& bIsSlotEmpty, uint8& Amount) const
{
	check(Slots.Num() > Index)

	const FIMInventorySlot Slot = Slots[Index];

	if (Slot.ItemData.IsValid())
	{
		TSoftObjectPtr<UBaseItemPrimaryDA> ItemInfo = Slot.ItemData;

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

	return Slots[Index].Amount;
}

void UIMInventoryComponent::ToggleInventory()
{
	if (bIsVisible)
	{
		HideInventory();
	}

	ShowInventory();
}

void UIMInventoryComponent::SetSlotAmount(const uint8 AmountOfSlots)
{
	SlotAmount = FMath::Clamp(static_cast<int32>(AmountOfSlots), 1, 1000);
}

void UIMInventoryComponent::SetMaxStackSize(const uint8 StackSize)
{
	MaxStackSize = FMath::Clamp(static_cast<int32>(StackSize), 1, 1000);
}

void UIMInventoryComponent::OnRegister()
{
	Super::OnRegister();

	PlayerCharacter = Cast<ACharacter>(GetOwner());

	if (IsValid(PlayerCharacter))
	{
		print("Valid player");
		if (IsValid(PlayerCharacter->InputComponent))
		{
			print("Valid input");
			EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerCharacter->InputComponent);

			if (IsValid(EnhancedInputComponent))
			{
				print("Valid enhanced");
				if (ToggleInventoryAction != nullptr)
				{
					print("Binded toggle");
					ToggleInventoryBindingHandle = EnhancedInputComponent->BindAction(
						ToggleInventoryAction, ETriggerEvent::Triggered, this,
						&UIMInventoryComponent::OnToggleInventory).GetHandle();
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
bool UIMInventoryComponent::SearchEmptySlot(int32& Index)
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
bool UIMInventoryComponent::SearchFreeStack(const TSoftObjectPtr<UBaseItemPrimaryDA> ItemData, int32& Index)
{
	bool bSlotAvaiable = false;
	int FoundIndex = 0;

	if (!Slots.IsEmpty())
	{
		FScopeLock Lock(&SocketsCriticalSection);

		for (int i = 0; i < Slots.Num(); i++)
		{
			if (!Slots[i].ItemData.IsNull())
			{
				if (Slots[i].ItemData == ItemData)
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

bool UIMInventoryComponent::AddUnstackableItem(TSoftObjectPtr<UBaseItemPrimaryDA> ItemData, const uint8 Amount,
                                             uint8& Rest)
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

bool UIMInventoryComponent::AddStackableItem(TSoftObjectPtr<UBaseItemPrimaryDA> ItemData, const uint8 Amount, uint8& Rest)
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

	print("Found free stack");
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

bool UIMInventoryComponent::RemoveItemAtIndex(const int32 Index, const uint8 Amount)
{
	if (!IsSlotEmpty(Index) && Amount > 0)
	{
		FScopeLock Lock(&SocketsCriticalSection);

		if (Amount >= GetAmountAtIndex(Index))
		{
			Slots[Index].ItemData = nullptr;
			Slots[Index].Amount = 0;

			UpdateSlotAtIndex(Index);

			return true;
		}

		Slots[Index].Amount -= Amount;

		UpdateSlotAtIndex(Index);

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

	Slots[TargetIndex].ItemData = Slots[OriginIndex].ItemData;
	Slots[TargetIndex].Amount = Slots[OriginIndex].Amount;

	Slots[OriginIndex].ItemData = TempSlot.ItemData;
	Slots[OriginIndex].Amount = TempSlot.Amount;

	UpdateSlotAtIndex(OriginIndex);
	UpdateSlotAtIndex(TargetIndex);

	return true;
}

bool UIMInventoryComponent::SplitStack(const int32 Index, uint8 Amount)
{
	if (IsSlotEmpty(Index))
	{
		return false;
	}

	bool bIsSlotEmpty = false;
	uint8 FoundSlotAmount = 0;
	const TSoftObjectPtr<UBaseItemPrimaryDA> ItemInfo = GetItemInfoAtIndex(Index, bIsSlotEmpty, FoundSlotAmount);

	if (!ItemInfo.IsNull())
	{
		if (FoundSlotAmount > Amount && ItemInfo->bCanBeStacked)
		{
			int32 FoundSlotIndex = 0;
			if (SearchEmptySlot(FoundSlotIndex))
			{
				FScopeLock Lock(&SocketsCriticalSection);

				Slots[Index].ItemData = ItemInfo;
				Slots[Index].Amount = FoundSlotAmount - Amount;

				Slots[FoundSlotIndex].ItemData = ItemInfo;
				Slots[FoundSlotIndex].Amount = Amount;

				UpdateSlotAtIndex(Index);
				UpdateSlotAtIndex(FoundSlotIndex);

				return true;
			}
		}
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

void UIMInventoryComponent::SetInventoryWidget(UIMInventoryWidget* InventoryWidgetRef)
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

UIMInventoryWidget* UIMInventoryComponent::GetInventoryWidget() const
{
	return InventoryWidget;
}

bool UIMInventoryComponent::AddItem(TSoftObjectPtr<UBaseItemPrimaryDA> ItemData, const uint8 Amount, uint8& Rest)
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


bool UIMInventoryComponent::OnAddItemToInventory_Implementation(UObject* ItemToAdd)
{
	AIMItemPickup* Item = Cast<AIMItemPickup>(ItemToAdd);

	if (Item)
	{
		uint8 Rest = 0;

		return AddItem(Item->GetItemData(), 1, Rest);
	}

	return false;
}
