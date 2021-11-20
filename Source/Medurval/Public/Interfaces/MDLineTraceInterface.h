// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MDLineTraceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMDLineTraceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDURVAL_API IMDLineTraceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void StartLineTrace();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void EndLineTrace();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	bool IsLineTraceEnabled() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	AActor* GetLineTraceHitActor() const;
};
