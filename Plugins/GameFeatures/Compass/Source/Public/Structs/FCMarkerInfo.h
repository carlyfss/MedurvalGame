#pragma once

#include "Enums/ECMarkerTypes.h"
#include "FCMarkerInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "DirectionInfo"))
struct COMPASS_API FCMarkerInfo
{
    GENERATED_BODY()

    FORCEINLINE FCMarkerInfo();

    FORCEINLINE FCMarkerInfo(ECMarkerTypes MarkerType, FVector TargetLocation);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MarkerInfo")
    ECMarkerTypes Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MarkerInfo")
    FVector Location;
};

inline FCMarkerInfo::FCMarkerInfo()
{
    Type = ECMarkerTypes::Default;
    Location = FVector(0, 0, 0);
}

inline FCMarkerInfo::FCMarkerInfo(ECMarkerTypes MarkerType, FVector TargetLocation)
{
    Type = MarkerType;
    Location = TargetLocation;
}