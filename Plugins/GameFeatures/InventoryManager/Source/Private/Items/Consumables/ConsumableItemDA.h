// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Items/InventoryItemDA.h"
#include "ConsumableItemDA.generated.h"

/**
 * 
 */
UCLASS()
class UConsumableItemDA : public UInventoryItemDA
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	int Type = 0;
	
};
