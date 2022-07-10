// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSBuildingActor.h"

#include "Components/CBStaticMeshComponent.h"
#include "Components/SSMaintenanceComponent.h"

ASSBuildingActor::ASSBuildingActor()
{
    Mesh = CreateDefaultSubobject<UCBStaticMeshComponent>("BuildingMesh");
    Maintenance = CreateDefaultSubobject<USSMaintenanceComponent>("MaintenanceComponent");
}
