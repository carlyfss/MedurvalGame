// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSBasePopupWidget.h"
#include "SSConstructionProgressWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConstructionComplete, ASSTerrainActor*, TerrainActor);

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSConstructionProgressWidget : public USSBasePopupWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ConstructionProgressWidget")
    void StartConstructionTimer();
    
    virtual void UpdateWidget_Implementation() override;
    virtual void UpdateWidgetInfo_Implementation(ASSTerrainActor *TerrainActor) override;
    virtual void StartUpdatingPosition_Implementation() override;
    virtual void StopUpdatingPosition_Implementation() override;
};
