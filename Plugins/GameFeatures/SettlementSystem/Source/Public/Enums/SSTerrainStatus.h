// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "TerrainStatus"))
enum class ESSTerrainStatus : uint8
{
    Unclaimed,
    Claimed,
    Constructed
};
