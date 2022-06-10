// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYMANAGER_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_Inventory|Interaction")
	bool OnAddItemToInventory(UObject* ItemToAdd);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_Inventory|Interaction")
	void UpdateSlotAfterLoad(uint8 SlotIndex);
};
