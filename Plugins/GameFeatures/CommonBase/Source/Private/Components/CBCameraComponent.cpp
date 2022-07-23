// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/CBCameraComponent.h"
#include "Constants/CBConstants.h"

UCBCameraComponent::UCBCameraComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FCBConstants::TickInterval;

    bUsePawnControlRotation = false;
}
