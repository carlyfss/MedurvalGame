// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/CBActor.h"

#include "Constants/CommonBaseConstants.h"

// Sets default values
ACBActor::ACBActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickInterval = FCommonBaseConstants::TickInterval;
}

