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
    TObjectPtr<ACharacter> PlayerReference = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASSTerrainActor> SelectedTerrain = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="SettlementWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementComponent> SettlementReference = nullptr;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void OpenTerrainInfo(ASSTerrainActor* TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void CloseTerrainInfo();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="SettlementWidget")
    void SetBindOnUpdateTreasury();
};
