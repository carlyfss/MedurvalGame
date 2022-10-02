// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "MDInventorySlot.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "InventorySlot"))
struct MEDURVAL_API FMDInventorySlot
{
	GENERATED_BODY()

	inline static constexpr int32 MAX_SlotAmount = 150;
	inline static constexpr int32 MIN_SlotAmount = 0;

	FMDInventorySlot() : Item(FPrimaryAssetId()), Amount(0)
	{
	}

	FMDInventorySlot(FPrimaryAssetId NewItem, int32 NewAmount) : Item(NewItem), Amount(NewAmount)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlot")
	FPrimaryAssetId Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySlot")
	int32 Amount;

	/**
	 * Add to the current slot amount and if amount to add is greater than MAX_SlotAmount returns the rest.
	*/
	int32 AddAmount(int32 ToAddAmount)
	{
		int32 Rest;
		const int32 Sum = Amount + ToAddAmount;

		if (Sum > MAX_SlotAmount)
		{
			Amount = MAX_SlotAmount;
			Rest = Sum - MAX_SlotAmount;
		}
		else
		{
			Amount = FMath::Clamp(Sum, MIN_SlotAmount, MAX_SlotAmount);
			Rest = 0;
		}

		return Rest;
	}

	/**
	 * Remove the amount and clamp the result.
	 * @returns Current slot amount
	*/
	int32 RemoveAmount(int32 ToRemoveAmount)
	{
		Amount = FMath::Clamp(Amount - ToRemoveAmount, MIN_SlotAmount, MAX_SlotAmount);
		return Amount;
	}

	bool operator!() const
	{
		return !Item.IsValid() && Amount != 0;
	}

	bool operator!=(const FMDInventorySlot& other) const
	{
		return other.Item.PrimaryAssetType != Item.PrimaryAssetType;
	}

	bool operator==(const FMDInventorySlot& other) const
	{
		return other.Item.PrimaryAssetType == Item.PrimaryAssetType;
	}

	void ClearSlot()
	{
		Item = FPrimaryAssetId();
		Amount = 0;
	}

	bool IsSameItem(FPrimaryAssetId ItemToCompare)
	{
		return Item.PrimaryAssetType == ItemToCompare.PrimaryAssetType;
	}

	bool IsFull() const
	{
		return Amount == MAX_SlotAmount;
	}

	bool IsEmpty() const
	{
		return Amount == 0;
	}

	bool IsValid() const
	{
		return Item.IsValid() && Amount > 0;
	}
};

