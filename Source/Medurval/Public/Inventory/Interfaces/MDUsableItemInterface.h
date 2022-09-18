// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MDUsableItemInterface.generated.h"

class AActor;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMDUsableItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDURVAL_API IMDUsableItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="MDUsableItemInterface")
	void UseItem(AActor* ItemOwner);
};
