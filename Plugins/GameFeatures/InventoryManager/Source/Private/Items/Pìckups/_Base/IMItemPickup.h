// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBActor.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MDInteractableInterface.h"
#include "IMItemPickup.generated.h"

class UCBSphereComponent;
class UCBStaticMeshComponent;
class UIMInventoryComponent;
class UIMBaseItemDA;

UCLASS(meta=(DisplayName="InventoryItemPickup"))
class AIMItemPickup : public ACBActor, public IMDInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	bool bIsPickupReady = false;

	UPROPERTY(Transient)
	TObjectPtr<AActor> OverlapedActor = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UIMBaseItemDA> LoadedItem = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetItemData, Category="_Pickup")
	TSoftObjectPtr<UIMBaseItemDA> ItemData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="_Pickup|Base", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMesh> DefaultStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="_Pickup", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBSphereComponent> PickupRange = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="_Pickup", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="_Pickup|Configuration")
	float PickupRangeRadius = 200;

	UPROPERTY(EditDefaultsOnly, Category="_Pickup")
	uint8 AmountToAdd = 1;

public:
	// Sets default values for this actor's properties
	AIMItemPickup();

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
	void OnPickupStartFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void OnPickupEndFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="_ItemInteraction")
	void OnPickupInteract();

	virtual void OnInteract_Implementation() override;

	virtual void OnStartFocus_Implementation() override;

	virtual void OnEndFocus_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="_ItemInteraction")
	TSoftObjectPtr<UIMBaseItemDA> GetItemData() const;
};
