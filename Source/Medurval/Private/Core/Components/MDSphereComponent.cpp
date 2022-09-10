// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDSphereComponent.h"
#include "Constants/CBConstants.h"

UMDSphereComponent::UMDSphereComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;
}
