// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDDirectionWidget.h"
#include "MDMarkerWidget.h"
#include "Compass/Structs/MDDirectionInfo.h"
#include "Components/OverlaySlot.h"
#include "MDCompassWidget.generated.h"

class UOverlay;
class UImage;

/**
 *
 */
UCLASS()
class MEDURVAL_API UMDCompassWidget : public UMDActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UOverlay *CompassOverlay;

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UImage *CompassImage;

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true))
    TArray<UMDDirectionWidget*> DirectionWidgets;

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true))
    TArray<UMDMarkerWidget*> MarkerWidgets;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CompassWidget")
    UOverlaySlot* AddDirection(FMDDirectionInfo Direction);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CompassWidget")
    UOverlaySlot* AddMarker(EMDMarkerTypes Type);

    TArray<UMDDirectionWidget*> GetDirectionWidgets();
};
