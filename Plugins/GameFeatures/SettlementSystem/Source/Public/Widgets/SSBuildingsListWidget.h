// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSBaseWidget.h"
#include "SSBuildingsListWidget.generated.h"

class ASSTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBuildingsListWidget : public USSBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListItem")
    void CloseWidget();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListItem")
    void LoadAvailableBuildings(ASSTerrainActor *TerrainActor);
};
