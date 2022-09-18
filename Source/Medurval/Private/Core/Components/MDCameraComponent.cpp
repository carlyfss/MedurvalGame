// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDCameraComponent.h"
#include "Core/Constants/MDConstants.h"

UMDCameraComponent::UMDCameraComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;

    bUsePawnControlRotation = false;
}
