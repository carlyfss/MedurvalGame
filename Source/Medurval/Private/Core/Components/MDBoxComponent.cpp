// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDBoxComponent.h"
#include "Constants/CBConstants.h"

UMDBoxComponent::UMDBoxComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;
}
