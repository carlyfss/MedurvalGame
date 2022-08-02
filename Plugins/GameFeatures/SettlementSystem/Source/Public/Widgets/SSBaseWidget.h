// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SSBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBaseWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="BaseWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<ACharacter> PlayerReference = nullptr;

protected:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BaseWidget")
    void InitializeWidget();
    
public:
    UFUNCTION(BlueprintCallable, Category="BaseWidget")
    virtual void SetWidgetVisibility(bool bIsVisible);
};
