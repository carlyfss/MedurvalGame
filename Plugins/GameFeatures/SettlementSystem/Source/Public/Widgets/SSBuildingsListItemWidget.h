// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SSBaseWidget.h"
#include "SSBuildingsListItemWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingListItemSelected);

class USSBuildingDA;

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBuildingsListItemWidget : public USSBaseWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="BuildingsListItemWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSBuildingDA> BuildingDataReference;

public:
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnBuildingListItemSelected OnBuildingListItemSelected;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListItemWidget")
    void SetupWidget(FPrimaryAssetId BuildingId);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListItemWidget")
    void SelectItem();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingsListItemWidget")
    void DeselectItem();
    
};
