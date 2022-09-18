#pragma once

#include "MDDirectionInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "DirectionInfo"))
struct MEDURVAL_API FMDDirectionInfo
{
    GENERATED_BODY()

    FORCEINLINE FMDDirectionInfo();

    FORCEINLINE FMDDirectionInfo(FText DirectionName, int DirectionRotation);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionInfo")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DirectionInfo")
    int WorldRotation;
};

inline FMDDirectionInfo::FMDDirectionInfo()
{
    WorldRotation = 0;
}

inline FMDDirectionInfo::FMDDirectionInfo(FText DirectionName, int DirectionRotation)
{
    Name = DirectionName;
    WorldRotation = DirectionRotation;
}
