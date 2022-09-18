// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDStaticMeshComponent.h"
#include "Core/Constants/MDConstants.h"

UMDStaticMeshComponent::UMDStaticMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}
