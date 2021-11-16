// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PickupInterface.h"
#include "BaseItemPickup.generated.h"

class UInventoryComponent;
class UBaseItemPrimaryDA;
class UStaticMeshComponent;
class USphereComponent;
class UPrimitiveComponent;

UCLASS(meta = (DisplayName = "BaseItemPickup"))
class ABaseItemPickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	bool bIsPickupReady = false;

	UPROPERTY(Transient)
	TObjectPtr<AActor> OverlapedActor = nullptr;

	TObjectPtr<UBaseItemPrimaryDA> LoadedItem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="_Pickup|Base")
	TObjectPtr<UStaticMesh> DefaultStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> PickupRange = nullptr;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<UStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="_Pickup|Configuration")
	float PickupRangeRadius = 200;

	UPROPERTY(EditDefaultsOnly, Category="_Pickup")
	TSoftObjectPtr<UBaseItemPrimaryDA> ItemData = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="_Pickup")
	uint8 AmountToAdd = 1;
	
public:
	// Sets default values for this actor's properties
	ABaseItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void LoadPickupItem();

	// declare overlap begin function
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                             bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category="_Pickup|Configuration")
	virtual void AddItemToInventory();

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void OnStartPickupFocus_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void OnEndPickupFocus_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void OnInteract_Implementation() override;
};
