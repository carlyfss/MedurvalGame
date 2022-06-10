// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MDDataAssetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMDDataAssetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDURVAL_API IMDDataAssetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, Category="Data Asset Interface")
	void OnAssetsLoaded();

	UFUNCTION(BlueprintNativeEvent, Category="Data Asset Interface")
	void RequestAsyncLoadAssets(AActor* ObjectOwner);

	UFUNCTION(BlueprintNativeEvent, Category="Data Asset Interface")
	void UnloadAssets(AActor* ObjectOwner);
};
