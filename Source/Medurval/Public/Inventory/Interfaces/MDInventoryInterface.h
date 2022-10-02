// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MDInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (DisplayName = "MDInventoryInterface"))
class UMDInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDURVAL_API IMDInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="MDInventoryInterface")
	bool OnAddItemToInventory(FPrimaryAssetId ItemIdToAdd, int32 Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="MDInventoryInterface")
	bool RemoveItemFromInventory(FPrimaryAssetId ItemIdToRemove, int32 Amount, int32& Rest);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="MDInventoryInterface")
	void UpdateSlotAfterLoad(int32 SlotIndex);
};
