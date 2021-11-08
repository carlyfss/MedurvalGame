// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Items/Pìckups/_Base/BaseItemPickup.h"
#include "ConsumableItemPickup.generated.h"

UCLASS()
class INVENTORYMANAGER_API AConsumableItemPickup : public ABaseItemPickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConsumableItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
};
