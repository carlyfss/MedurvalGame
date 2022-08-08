// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SSBaseWidget.generated.h"

class UMDGameInstance;
/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBaseWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseWidget")
    void InitializeWidget();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="SSActor")
    UMDGameInstance* GetMDGameInstance() const;
    
public:
    UFUNCTION(BlueprintCallable, Category="BaseWidget")
    virtual void SetWidgetVisibility(bool bIsVisible);
};
