// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "Inventory/Interfaces/MDInventoryInterface.h"
#include "Inventory/Structs/MDInventoryEquipmentSlot.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "Inventory/Structs/MDInventoryWeaponSlot.h"
#include "MDInventoryComponent.generated.h"

class AMDPlayerCharacter;
class UMDInventoryWidget;
class UMDItemDataAsset;
class UInputMappingContext;

UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "InventoryComponent"))
class MEDURVAL_API UMDInventoryComponent : public UMDActorComponent, public IMDInventoryInterface
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(Transient)
	TObjectPtr<AMDPlayerCharacter> PlayerCharacter = nullptr;

#pragma region Configurations
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	int32 SlotAmount = 24;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	int32 EquipmentSlotsAmount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	int32 WeaponSlotsAmount = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	int32 SidebarEquipmentSlotAmount = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	TMap<EMDEquipmentAttachment, TSoftObjectPtr<UTexture2D>> EquipmentSlotsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	TMap<EMDWeaponAttachment, TSoftObjectPtr<UTexture2D>> WeaponSlotsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	uint8 SlotsPerRow = 6;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	uint8 MaxStackSize = 150;
#pragma endregion Configurations

	UPROPERTY(BlueprintReadWrite, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
	bool bIsVisible = false;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventorySlot> Slots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventoryEquipmentSlot> EquipmentSlots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventoryWeaponSlot> WeaponSlots;

protected:
	virtual void BeginPlay() override;

	bool SearchEmptySlot(uint8& Index);

	bool SearchFreeStack(UMDItemDataAsset* Item, uint8& Index);

	bool SearchItem();

	bool AddUnstackableItem(UMDItemDataAsset* Item, uint8 Amount, uint8& Rest);

	bool AddStackableItem(UMDItemDataAsset* Item, uint8 Amount, uint8& Rest);

#pragma region Interaction
	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool AddItem(UMDItemDataAsset* Item, uint8 Amount, uint8& Rest);

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
	UMDItemDataAsset* GetItemInfoAtIndex(uint8 Index, bool& bIsSlotEmpty, uint8& Amount) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	uint8 GetAmountAtIndex(uint8 Index) const;

	TArray<FMDInventorySlot> GetSlots() const;

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UMDItemDataAsset *, ItemAdded, uint8, Amount);

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemRemoved, UMDItemDataAsset *, ItemRemoved, uint8, Amount,
	                                               uint8, Index);

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateSlotAtIndex, uint8, SlotIndex);

	UPROPERTY(BlueprintAssignable)
	FOnUpdateSlotAtIndex OnUpdateSlotAtIndex;
#pragma endregion Delegate;

	virtual bool OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToRemove, uint8 Amount) override;

	virtual void UpdateSlotAfterLoad_Implementation(uint8 SlotIndex) override;

	virtual bool RemoveItemFromInventory_Implementation(FPrimaryAssetId ItemIdToAdd, uint8 Amount, int& Rest) override;

	uint8 GetSlotsPerRow() const;
};
