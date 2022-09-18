// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MDActivatableWidget.generated.h"

class UMDGameInstance;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="MDActivatableWidget")
    void InitializeWidget();
};
