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

	UFUNCTION(BlueprintCallable, Category="_MDController")
	void SetInputModeGameOnly(bool InConsumeCaptureMouseDown);
};
