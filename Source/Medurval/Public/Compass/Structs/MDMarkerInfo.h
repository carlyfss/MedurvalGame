#pragma once

#include "Compass/Enums/MDMarkerTypes.h"
#include "MDMarkerInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "MarkerInfo"))
struct MEDURVAL_API FMDMarkerInfo
{
	GENERATED_BODY()

	FORCEINLINE FMDMarkerInfo();

	FORCEINLINE FMDMarkerInfo(EMDMarkerTypes MarkerType, FVector TargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MarkerInfo")
	EMDMarkerTypes Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MarkerInfo")
	FVector Location;
};

inline FMDMarkerInfo::FMDMarkerInfo()
{
	Type = EMDMarkerTypes::Default;
	Location = FVector(0, 0, 0);
}

inline FMDMarkerInfo::FMDMarkerInfo(EMDMarkerTypes MarkerType, FVector TargetLocation)
{
	Type = MarkerType;
	Location = TargetLocation;
}
