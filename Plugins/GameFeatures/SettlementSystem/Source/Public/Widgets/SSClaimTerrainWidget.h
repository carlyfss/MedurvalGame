// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSBaseWidget.h"
#include "SSClaimTerrainWidget.generated.h"

class ASSTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSClaimTerrainWidget : public USSBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void UpdateWidgetInfo(ACharacter *CharacterReference, ASSTerrainActor *TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void StartUpdatingPosition();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void StopUpdatingPosition();
};
