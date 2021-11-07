// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventorySlot.h"
#include "InventoryComponent.generated.h"

class ACharacter;
class UInventoryItemDA;

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

	UInventoryItemDA* GetItemInfoAtIndex(const int Index, bool& bIsSlotEmpty, int& Amount) const;

	int GetAmountAtIndex(const int Index) const;
	
	bool SearchEmptySlot(int& Index);

	bool SearchFreeStack(const TSoftClassPtr<UInventoryItemDA> ItemClass, int& Index);

	bool AddUnstackableItem(TSoftClassPtr<UInventoryItemDA> ItemClass, int Amount, int& Rest);

	bool AddStackableItem(TSoftClassPtr<UInventoryItemDA> ItemClass, int Amount, int& Rest);

public:

	UFUNCTION(BlueprintCallable, Category="Inventory|References")
	void SetPlayerReference(ACharacter* PlayerRef);
	
	UFUNCTION(Category="Inventory|Interaction")
	bool AddItem(const TSoftClassPtr<UInventoryItemDA> ItemClass, int Amount, int& Rest);
};
