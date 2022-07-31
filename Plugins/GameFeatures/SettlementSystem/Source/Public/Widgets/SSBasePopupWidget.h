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

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void UpdateWidgetInfo(ACharacter *CharacterReference, ASSTerrainActor *TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void StartUpdatingPosition();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ClaimTerrainWidget")
    void StopUpdatingPosition();

    
};
