// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"

struct SETTLEMENTS_API FSTTerrainConstants
{
public:
    inline static uint8 MaxSizeSmall = 8;

    inline static uint8 MinSizeSmall = 1;

    inline static uint8 MaxSizeMedium = 20;

    inline static uint8 MinSizeMedium = MaxSizeSmall;

    inline static uint8 MaxSizeLarge = 40;

    inline static uint8 MinSizeLarge = MaxSizeMedium;

    inline static uint8 DefaultTargetHeight = 40;

    inline static float UnitsPerMeter = 100.f;

    inline static FLinearColor DefaultTargetColor = FLinearColor::White;

    inline static FLinearColor DefaultSelectedTargetColor = FLinearColor(0.9f, 0.75f, 0.f);

    inline static FLinearColor DefaultUnclaimedTargetColor = FLinearColor(0.1f, 0.1f, 0.1f);

    inline static FName TargetColorParameterName = FName(TEXT("BaseColor"));
};
