// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ECMarkerTypes.h"
#include "CMarkerWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class COMPASS_API UCMarkerWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UTextBlock *DistanceText;

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UImage *MarkerIcon;

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true))
    ECMarkerTypes Type;

    UPROPERTY(BlueprintReadWrite, Category = "MarkerWidget", meta = (AllowPrivateAccess = true))
    int MaxDisplayDistance = 10000;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "MarkerWidget")
    void UpdateDistance(int Distance) const;
};
