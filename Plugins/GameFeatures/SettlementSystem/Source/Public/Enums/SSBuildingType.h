// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "BuildingType"))
enum class ESSBuildingType : uint8
{
    Civilian,
    Military,
    Store,
    Auxiliary,
    Storage,
    Entertainment
};
