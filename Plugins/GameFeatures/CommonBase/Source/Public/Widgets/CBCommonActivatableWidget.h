// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CBCommonActivatableWidget.generated.h"

class UMDGameInstance;
/**
 * 
 */
UCLASS()
class COMMONBASE_API UCBCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseWidget")
    void InitializeWidget();
};
