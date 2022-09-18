// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MDActivatableWidget.generated.h"

class UMedurvalAssetManager;
class AMDPlayerController;
class UMDGameInstance;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="MDActivatableWidget")
    void InitializeWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDActivatableWidget")
	void UpdateWidget();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
	UMDGameInstance* GetMDGameInstance() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
	AMDPlayerController* GetMDPlayerController() const;
};
