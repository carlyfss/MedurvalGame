#pragma once

#include "FCDirectionInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "DirectionInfo"))
struct COMPASS_API FCDirectionInfo
{
    GENERATED_BODY()

    FORCEINLINE FCDirectionInfo();

    FORCEINLINE FCDirectionInfo(FText DirectionName, int DirectionRotation);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionInfo")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionInfo")
    int WorldRotation;
};

inline FCDirectionInfo::FCDirectionInfo()
{
    WorldRotation = 0;
}

inline FCDirectionInfo::FCDirectionInfo(FText DirectionName, int DirectionRotation)
{
    Name = DirectionName;
    WorldRotation = DirectionRotation;
}
