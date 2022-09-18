// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDSkeletalMeshComponent.h"
#include "Core/Constants/MDConstants.h"

UMDSkeletalMeshComponent::UMDSkeletalMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}
