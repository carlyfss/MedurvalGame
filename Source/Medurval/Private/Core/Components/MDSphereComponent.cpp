// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDSphereComponent.h"
#include "Core/Constants/MDConstants.h"

UMDSphereComponent::UMDSphereComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}
