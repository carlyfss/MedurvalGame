// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/CBSphereComponent.h"

#include "Constants/CBConstants.h"

UCBSphereComponent::UCBSphereComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;
}
