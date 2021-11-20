// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Items/Pìckups/_Base/IMItemPickup.h"
#include "IMConsumableItemPickup.generated.h"

UCLASS(meta=(DisplayName="InventoryConsumableItemPickup"))
class INVENTORYMANAGER_API AIMConsumableItemPickup : public AIMItemPickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIMConsumableItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
};
