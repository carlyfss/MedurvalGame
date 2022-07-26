// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Actors/SSTerrainActor.h"
#include "SSSettlementManagementWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSSettlementManagementWidget : public UCommonUserWidget
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<ACharacter> PlayerReference;

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASSTerrainActor> SelectedTerrain;

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementComponent> SettlementReference;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void OpenTerrainInfo(ASSTerrainActor* TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void SetBindOnUpdateTreasury();
};
