// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Actors/CBActor.h"

#include "Constants/CBConstants.h"

// Sets default values
ACBActor::ACBActor()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.TickInterval = FCBConstants::TickInterval;
}

void ACBActor::StartTimerWithDelegate()
{
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ACBActor::TimerDelegate, TimerInterval, bIsToLoopTimer, TimerStartDelay);
}

void ACBActor::StopTimer()
{
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ACBActor::TimerDelegate()
{
    return;
}
