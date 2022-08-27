// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "STBaseWidget.generated.h"

class AMDPlayerController;
class UMDGameInstance;
/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTBaseWidget : public UCBCommonActivatableWidget
{
    GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="SSActor")
    UMDGameInstance* GetMDGameInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="SSActor")
    AMDPlayerController* GetMDPlayerController() const;
    
public:
    virtual void NativeOnDeactivated() override;

};