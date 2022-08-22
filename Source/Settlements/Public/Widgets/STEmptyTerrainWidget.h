// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "STBasePopupWidget.h"
#include "STEmptyTerrainWidget.generated.h"

class USTSettlementManagementWidget;

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTEmptyTerrainWidget : public USTBasePopupWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="ClaimTerrainWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementManagementWidget> SettlementManagementWidget;
};
