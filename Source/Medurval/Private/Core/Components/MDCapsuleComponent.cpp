// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDCapsuleComponent.h"
#include "Constants/CBConstants.h"

UMDCapsuleComponent::UMDCapsuleComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;
}
