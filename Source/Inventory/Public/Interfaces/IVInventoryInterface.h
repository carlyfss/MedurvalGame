// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IVInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (DisplayName = "InventoryInterface"))
class UIVInventoryInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 
 */
class INVENTORY_API IIVInventoryInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="InventoryInterface")
    bool OnAddItemToInventory(FPrimaryAssetId ItemIdToAdd, uint8 Amount);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="InventoryInterface")
    bool RemoveItemFromInventory(FPrimaryAssetId ItemIdToRemove, uint8 Amount, int &Rest);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="InventoryInterface")
    void UpdateSlotAfterLoad(uint8 SlotIndex);
};
