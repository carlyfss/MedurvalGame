// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "IMConsumableItemPickup.h"


// Sets default values
AIMConsumableItemPickup::AIMConsumableItemPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickInterval = 0.075f;
}

// Called when the game starts or when spawned
void AIMConsumableItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

