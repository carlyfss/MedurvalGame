// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventorySlot.h"
#include "InventoryComponent.generated.h"

class ACharacter;
class UBaseItemDA;

UCLASS()
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	FCriticalSection SocketsCriticalSection;

	UPROPERTY(Transient)
	uint8 SlotAmount = 10;

	UPROPERTY(Transient)
	uint8 MaxStackSize = 30;

	UPROPERTY(BlueprintSetter=SetPlayerReference, Category="Inventory|Configuration")
	TObjectPtr<ACharacter> PlayerReference = nullptr;

protected:

	UPROPERTY(Transient)
	TArray<FInventorySlot> Slots;
	
public:	
	// Sets default values for this actor's properties
	UInventoryComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool IsSlotEmpty(const int32 Index) const;

	TSoftObjectPtr<UBaseItemDA> GetItemInfoAtIndex(const int32 Index, bool& bIsSlotEmpty, uint8& Amount) const;
	
	bool SearchEmptySlot(int32& Index);

	bool SearchFreeStack(const TSoftObjectPtr<UBaseItemDA> ItemData, int32& Index);

	bool AddUnstackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, uint8 Amount, uint8& Rest);

	bool AddStackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, uint8 Amount, uint8& Rest);

public:

	int GetAmountAtIndex(const int32 Index) const;

	UFUNCTION(BlueprintCallable, Category="Inventory|Configurations")
	void SetSlotAmount(const uint8 AmountOfSlots);

	UFUNCTION(BlueprintCallable, Category="Inventory|Configurations")
	void SetMaxStackSize(const uint8 StackSize);

	UFUNCTION(BlueprintCallable, Category="Inventory|References")
	void SetPlayerReference(ACharacter* PlayerRef);
	
	UFUNCTION(Category="Inventory|Interaction")
	bool AddItem(const TSoftObjectPtr<UBaseItemDA> ItemClass, uint8 Amount, uint8& Rest);
};
