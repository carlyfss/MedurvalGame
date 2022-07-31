// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSBaseWidget.h"
#include "SSBuildingsListWidget.generated.h"

class USSSettlementManagementWidget;
class ASSTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBuildingsListWidget : public USSBaseWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="BuildingsListWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementManagementWidget> SettlementManagementWidget;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListWidget")
    void CloseWidget();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListWidget")
    void LoadAvailableBuildings(ASSTerrainActor *TerrainActor);
};
