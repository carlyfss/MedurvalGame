// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CDirectionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/OverlaySlot.h"
#include "Structs/FCDirectionInfo.h"
#include "CCompassWidget.generated.h"

class UOverlay;
class UImage;

/**
 *
 */
UCLASS()
class COMPASS_API UCCompassWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UOverlay *CompassOverlay;

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UImage *CompassImage;

    UPROPERTY(BlueprintReadWrite, Category = "CompassWidget", meta = (AllowPrivateAccess = true, BindWidget))
    TArray<FCDirectionInfo> DirectionWidgets;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CompassWidget")
    UOverlaySlot *AddDirection(FCDirectionInfo Direction);
};
