// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InventoryInterface.h"
#include "IMInventorySlotWidget.generated.h"

class UMDGameInstance;
class UIMBaseItemDA;
class UIMInventoryComponent;
class UTextBlock;
class UButton;
class UImage;

UCLASS(meta=(DisplayName="InventorySlotWidget"))
class UIMInventorySlotWidget final : public UUserWidget, public IInventoryInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient, BlueprintGetter=GetItemAtSlot)
	TObjectPtr<UIMBaseItemDA> ItemAtSlot = nullptr;

	UPROPERTY(Transient, BlueprintGetter=GetSlotIndex, BlueprintSetter=SetSlotIndex)
	int SlotIndex = 0;

	UPROPERTY(Transient, BlueprintGetter=GetItemData, BlueprintSetter=SetItemData)
	TSoftObjectPtr<UIMBaseItemDA> ItemData = nullptr;

	UPROPERTY(Transient, BlueprintGetter=GetAmount, BlueprintSetter=SetAmount)
	uint8 Amount;

	UPROPERTY(Transient, BlueprintSetter=SetInventoryReference, BlueprintGetter=GetInventoryReference)
	TObjectPtr<UIMInventoryComponent> InventoryReference;

	UPROPERTY(Transient, BlueprintSetter=SetPlayerGameInstance, BlueprintGetter=GetPlayerGameInstance)
	TObjectPtr<UMDGameInstance> PlayerGameInstance;

	// Widget Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UButton> SlotButton = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UImage> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_InventorySlot", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> AmountText = nullptr;

	TArray<FSoftObjectPath> AssetsSoftPaths;

protected:
	void SetObjectsAfterLoad();

public:
	UFUNCTION(BlueprintCallable, Category="_InventorySlot")
	void UpdateSlot();

	UFUNCTION(BlueprintCallable, Category="_InventorySlot")
	void LoadSlotData();

	UFUNCTION(BlueprintCallable, Category="_InventorySlot")
	void UnloadSlotData();

	UFUNCTION(BlueprintCallable, Category="_InventorySlot")
	void CleanSlot();

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetInventoryReference(UIMInventoryComponent* TargetInventory);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	UButton* GetSlotButton() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	UIMInventoryComponent* GetInventoryReference() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetPlayerGameInstance(UMDGameInstance* TargetGameInstance);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	UMDGameInstance* GetPlayerGameInstance() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	uint8 GetAmount() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetAmount(const uint8 NewAmount);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	TSoftObjectPtr<UIMBaseItemDA> GetItemData() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetItemData(const TSoftObjectPtr<UIMBaseItemDA> NewItemData);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	int32 GetSlotIndex() const;

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Setter")
	void SetSlotIndex(const int32 Index);

	UFUNCTION(BlueprintCallable, Category="_InventorySlot|Getter")
	UIMBaseItemDA* GetItemAtSlot() const;
};
