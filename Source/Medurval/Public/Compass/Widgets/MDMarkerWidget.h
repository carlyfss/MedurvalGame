// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Compass/Enums/MDMarkerTypes.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "MDMarkerWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDMarkerWidget : public UMDActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UTextBlock *DistanceText;

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UImage *MarkerIcon;

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true))
    EMDMarkerTypes Type;

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true))
    int MaxDisplayDistance = 10000;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "MarkerWidget")
    void UpdateDistance(int Distance) const;
};
