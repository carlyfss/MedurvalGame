// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "Inventory/Interfaces/MDInventoryInterface.h"
#include "Inventory/Structs/MDInventoryAccessorySlot.h"
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
	int32 EquipmentSlotsAmount = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Configuration",
		meta = (AllowPrivateAccess = true))
	int32 AccessorySlotsAmount = 5;
	
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
	int32 SlotsPerRow = 6;
#pragma endregion Configurations

	UPROPERTY(BlueprintReadWrite, Category = "Inventory|Configuration", meta = (AllowPrivateAccess = true))
	bool bIsVisible = false;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventorySlot> Slots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventoryEquipmentSlot> EquipmentSlots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventoryAccessorySlot> AccessorySlots;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TArray<FMDInventoryWeaponSlot> WeaponSlots;

protected:
	virtual void BeginPlay() override;

	bool SearchEmptySlot(int32& Index);

	bool SearchFreeStack(FPrimaryAssetId Item, int32& Index);

	bool AddUnstackableItem(FPrimaryAssetId Item, int32 Amount, int32& Rest);

	bool AddStackableItem(FPrimaryAssetId Item, int32 Amount, int32& Rest);

	void InitializeSlotArrays();

	void SetupEquipmentSlots();

	void SetupAccessorySlots();

	void SetupWeaponSlots();

#pragma region Interaction
	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool AddItem(FPrimaryAssetId Item, int32 Amount, int32& Rest);

	void AddItemOnLoadCompleted(FPrimaryAssetId TargetItemId, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool AddToIndex(int32 SourceIndex, int32 TargetIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool RemoveItemAtIndex(int32 Index, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool SwapSlots(int32 OriginIndex, int32 TargetIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool SplitStack(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Interaction")
	bool SplitStackToIndex(int32 SourceIndex, int32 TargetIndex, int32 Amount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory|Interaction")
	void UseItemAtIndex(int32 Index);
#pragma endregion Interaction

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsSlotEmpty(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FPrimaryAssetId GetItemInfoAtIndex(int32 Index, bool& bIsSlotEmpty, int32& Amount) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetAmountAtIndex(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FMDInventorySlot> GetSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FMDInventoryEquipmentSlot> GetEquipmentSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FMDInventoryAccessorySlot> GetAccessorySlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FMDInventoryWeaponSlot> GetWeaponSlots() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EquipItem(EMDEquipmentAttachment Attachment, FPrimaryAssetId ItemId);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UnequipItem(EMDEquipmentAttachment Attachment);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 FindSlotIndexByAttachment(EMDEquipmentAttachment Attachment, bool& bHasFound) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsSlotEmptyAtAttachment(EMDEquipmentAttachment Attachment) const;

#pragma region Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, FPrimaryAssetId, ItemAdded, int32, Amount);

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemRemoved, FPrimaryAssetId, ItemRemoved, int32, Amount,
	                                               int32, Index);

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateSlotAtIndex, int32, SlotIndex);

	UPROPERTY(BlueprintAssignable)
	FOnUpdateSlotAtIndex OnUpdateSlotAtIndex;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquipped, FPrimaryAssetId, Item, EMDEquipmentAttachment,
	                                             Attachment);

	UPROPERTY(BlueprintAssignable)
	FOnItemEquipped OnItemEquipped;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUnequipped, EMDEquipmentAttachment, Attachment);

	UPROPERTY(BlueprintAssignable)
	FOnItemUnequipped OnItemUnequipped;
#pragma endregion Delegate;

	virtual bool OnAddItemToInventory_Implementation(FPrimaryAssetId ItemIdToRemove, int32 Amount) override;

	virtual void UpdateSlotAfterLoad_Implementation(int32 SlotIndex) override;

	virtual bool RemoveItemFromInventory_Implementation(FPrimaryAssetId ItemIdToAdd, int32 Amount, int& Rest) override;

	int32 GetSlotsPerRow() const;

	int32 GetEquipmentSlotsAmount() const;

	int32 GetAccessorySlotsAmount() const;

	int32 GetWeaponSlotsAmount() const;
};
