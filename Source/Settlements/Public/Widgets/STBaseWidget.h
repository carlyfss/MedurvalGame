// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "STBaseWidget.generated.h"

class AMDPlayerController;
class UMDGameInstance;
/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTBaseWidget : public UMDActivatableWidget
{
    GENERATED_BODY()
    
public:
    virtual void NativeOnDeactivated() override;

};
