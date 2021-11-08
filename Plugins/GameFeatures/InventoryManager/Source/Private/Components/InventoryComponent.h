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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Configuration", meta=(AllowPrivateAccess=true))
	int AmountOfSlots = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Configuration", meta=(AllowPrivateAccess=true))
	int MaxStackSize = 30;

	UPROPERTY(BlueprintSetter=SetPlayerReference, Category="Configuration")
	TObjectPtr<ACharacter> PlayerReference = nullptr;

	UPROPERTY(Transient)
	TArray<FInventorySlot> Slots;
	
public:	
	// Sets default values for this actor's properties
	UInventoryComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsSlotEmpty(const int Index) const;

	TSoftObjectPtr<UBaseItemDA> GetItemInfoAtIndex(const int Index, bool& bIsSlotEmpty, int& Amount) const;
	
	bool SearchEmptySlot(int& Index);

	bool SearchFreeStack(const TSoftObjectPtr<UBaseItemDA> ItemData, int& Index);

	bool AddUnstackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, int Amount, int& Rest);

	bool AddStackableItem(TSoftObjectPtr<UBaseItemDA> ItemData, int Amount, int& Rest);

public:

	int GetAmountAtIndex(const int Index) const;

	UFUNCTION(BlueprintCallable, Category="Inventory|References")
	void SetPlayerReference(ACharacter* PlayerRef);
	
	UFUNCTION(Category="Inventory|Interaction")
	bool AddItem(const TSoftObjectPtr<UBaseItemDA> ItemClass, int Amount, int& Rest);
};
