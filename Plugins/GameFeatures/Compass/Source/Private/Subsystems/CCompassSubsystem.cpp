// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Subsystems/CCompassSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"

void UCCompassSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
}

void UCCompassSubsystem::Deinitialize()
{
}

void UCCompassSubsystem::SetDirections(TArray<FCDirectionInfo> DirectionInfos)
{
    Directions = DirectionInfos;
}

TArray<FCDirectionInfo> UCCompassSubsystem::GetDirections()
{
    return Directions;
}
