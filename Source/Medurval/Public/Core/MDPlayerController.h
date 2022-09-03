// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API AMDPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMDPlayerController();
    virtual ~AMDPlayerController() = default;

    UFUNCTION(BlueprintCallable, Category="MDController")
    void SetInputModeGameOnly(bool InConsumeCaptureMouseDown);
};
