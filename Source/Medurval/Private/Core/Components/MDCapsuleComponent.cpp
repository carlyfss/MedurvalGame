// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDCapsuleComponent.h"
#include "core/Constants/MDConstants.h"

UMDCapsuleComponent::UMDCapsuleComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}
