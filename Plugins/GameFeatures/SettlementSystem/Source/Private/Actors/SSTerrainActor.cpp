// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSTerrainActor.h"

void ASSTerrainActor::SetConstructedBuilding(ASSBuildingActor *Building)
{
    ConstructedBuilding = Building;
}

void ASSTerrainActor::SetAssignedBuilding(TSoftClassPtr<ASSBuildingActor> Building)
{
    AssignedBuilding = Building;
}
