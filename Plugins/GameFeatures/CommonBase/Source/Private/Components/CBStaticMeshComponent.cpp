// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/CBStaticMeshComponent.h"
#include "Constants/CBConstants.h"

UCBStaticMeshComponent::UCBStaticMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;
}
