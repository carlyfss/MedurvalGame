// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDActorComponent.h"
#include "Core/Constants/MDConstants.h"

UMDActorComponent::UMDActorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}