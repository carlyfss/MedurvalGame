// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/CBBoxComponent.h"
#include "Constants/CBConstants.h"

UCBBoxComponent::UCBBoxComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;
}
