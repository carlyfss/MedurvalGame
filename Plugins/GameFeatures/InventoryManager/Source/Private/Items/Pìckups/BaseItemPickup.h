// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItemPickup.generated.h"

class UInventoryItemDA;
class UStaticMesh;
class UStaticMeshComponent;
class USphereComponent;
class UPrimitiveComponent;

UCLASS(meta = (DisplayName = "BaseItemPickup"))
class ABaseItemPickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> PickupRange = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup|Configuration")
	float PickupRangeRadius = 200;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	TObjectPtr<UInventoryItemDA> ItemData = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	float AmountToAdd = 1;

public:
	// Sets default values for this actor's properties
	ABaseItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// declare overlap begin function
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                             bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnConstruction(const FTransform& Transform) override;
public:
};
