// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/STBaseWidget.h"
#include "DataAssets/STBuildingDA.h"
#include "STBuildingsListItemWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingListItemSelected, USTBuildingDA*, BuildingData);

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTBuildingsListItemWidget : public USTBaseWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="BuildingsListItemWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTBuildingDA> BuildingDataReference;

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
