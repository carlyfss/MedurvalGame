// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/SSTerrainActor.h"
#include "Widgets/SSBaseWidget.h"
#include "SSBasePopupWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBasePopupWidget : public USSBaseWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="BasePopupWidget", meta=(AllowPrivateAccess=true))
    FString UpdateWidgetFunctionName = FString(TEXT("UpdateWidget"));

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BasePopupWidget", meta=(AllowPrivateAccess=true))
    float ShowPopupDelay = 0.05f;
    
    void ShowPopupWidget();

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void UpdateWidgetInfo(ASSTerrainActor *TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void StartUpdatingPosition();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void StopUpdatingPosition();

    virtual void SetWidgetVisibility(bool bIsVisible) override;

    
};
