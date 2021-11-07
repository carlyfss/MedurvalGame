// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "ConsumableItemPickup.h"


// Sets default values
AConsumableItemPickup::AConsumableItemPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void AConsumableItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

