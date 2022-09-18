// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/STBaseWidget.h"
#include "STBasePopupWidget.generated.h"

class ASTTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTBasePopupWidget : public USTBaseWidget
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

    UFUNCTION(BlueprintCallable, Category="BasePopupWidget")
    void UpdatePopupWidget();

    UFUNCTION(BlueprintCallable, Category="BasePopupWidget")
    void StartUpdatingPosition();

    UFUNCTION(BlueprintCallable, Category="BasePopupWidget")
    void StopUpdatingPosition();

public:
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BasePopupWidget")
    void UpdateWidgetInfo(ASTTerrainActor *TerrainActor);
};
