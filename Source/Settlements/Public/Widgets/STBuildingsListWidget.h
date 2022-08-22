// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "STBaseWidget.h"
#include "STBuildingsListWidget.generated.h"

class USTSettlementManagementWidget;
class ASTTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTBuildingsListWidget : public USTBaseWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="BuildingsListWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementManagementWidget> SettlementManagementWidget;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListWidget")
    void CloseWidget();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListWidget")
    void LoadAvailableBuildings(ASTTerrainActor *TerrainActor);
};
