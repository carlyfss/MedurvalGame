// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSBasePopupWidget.h"
#include "SSSettlementManagementWidget.h"
#include "SSEmptyTerrainWidget.generated.h"

class ASSTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSEmptyTerrainWidget : public USSBasePopupWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="ClaimTerrainWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementManagementWidget> SettlementManagementWidget;

public:
    virtual void UpdateWidget_Implementation() override;
    virtual void UpdateWidgetInfo_Implementation(ASSTerrainActor *TerrainActor) override;
    virtual void StartUpdatingPosition_Implementation() override;
    virtual void StopUpdatingPosition_Implementation() override;
};
