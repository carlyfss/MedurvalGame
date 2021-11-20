// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMUsableItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIMUsableItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYMANAGER_API IIMUsableItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void UseItem(AActor* ItemOwner);
};
