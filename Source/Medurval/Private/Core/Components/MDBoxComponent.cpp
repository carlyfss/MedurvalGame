// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDBoxComponent.h"
#include "Core/Constants/MDConstants.h"

UMDBoxComponent::UMDBoxComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}
