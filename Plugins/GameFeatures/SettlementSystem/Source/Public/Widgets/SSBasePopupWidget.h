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

    UPROPERTY(EditDefaultsOnly, Category="BasePopupWidget", meta=(AllowPrivateAccess=true))
    FVector2D WidgetPositionOffset = FVector2D(50.f, 100.f);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BasePopupWidget")
    float UpdateWidgetInterval = 0.01f;

    UPROPERTY(BlueprintReadWrite, Category="BasePopupWidget")
    FVector TerrainLocation = FVector();
    
    FTimerHandle TimerHandle;

    UFUNCTION(BlueprintCallable, BlueprintCallable, Category="BasePopupWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintCallable, Category="BasePopupWidget")
    void StartUpdatingPosition();

    UFUNCTION(BlueprintCallable, BlueprintCallable, Category="BasePopupWidget")
    void StopUpdatingPosition();

public:
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BasePopupWidget")
    void UpdateWidgetInfo(ASSTerrainActor *TerrainActor);

};
