// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItemPickup.generated.h"

class UBaseItemDA;
class UStaticMeshComponent;
class USphereComponent;
class UPrimitiveComponent;

UCLASS(meta = (DisplayName = "BaseItemPickup"))
class ABaseItemPickup : public AActor
{
	GENERATED_BODY()

	bool bIsPickupReady = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> PickupRange = nullptr;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<UStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup|Configuration")
	float PickupRangeRadius = 200;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	TSoftObjectPtr<UBaseItemDA> ItemData = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	int AmountToAdd = 1;
	

public:
	// Sets default values for this actor's properties
	ABaseItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool ConstructPickupItem();

	// declare overlap begin function
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                             bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnConstruction(const FTransform& Transform) override;
public:
};
