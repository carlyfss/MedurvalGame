// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SSBaseWidget.h"
#include "SSTimerWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateTime, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerCompleted);

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSTimerWidget : public USSBaseWidget
{
	GENERATED_BODY()


public:
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateTime OnUpdateTime;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnTimerCompleted OnTimerCompleted;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TimerWidget")
    void SetupWidget(int Time);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TimerWidget")
    void StartTimer();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TimerWidget")
    void CompleteTimer();
};
