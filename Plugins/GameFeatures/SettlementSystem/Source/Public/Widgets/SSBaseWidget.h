// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CBCommonActivatableWidget.h"
#include "SSBaseWidget.generated.h"

class AMDPlayerController;
class UMDGameInstance;
/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBaseWidget : public UCBCommonActivatableWidget
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
