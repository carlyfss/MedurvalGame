// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/STBaseWidget.h"
#include "STSettlementManagementWidget.generated.h"

class ASTTerrainActor;
class USTSettlementComponent;

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTSettlementManagementWidget : public USTBaseWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASTTerrainActor> SelectedTerrain = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementComponent> SettlementReference = nullptr;

protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void OnTerrainSelected(ASTTerrainActor* TerrainActor);

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void OpenTerrainInfo(ASTTerrainActor *TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void CloseTerrainInfo();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void SetBindOnUpdateTreasury();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void OnTerrainClaimed();
};
