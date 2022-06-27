// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBActor.h"
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
	TObjectPtr<UIMBaseItemDA> LoadedItem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup", meta=(AllowPrivateAccess=true))
	FPrimaryAssetId ItemId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBSphereComponent> PickupLoadRange = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	uint8 AmountToAdd = 1;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	float PickupLoadRangeRadius = 200.f;
public:
	// Sets default values for this actor's properties
	AIMItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPickupItemLoaded();

	void LoadPickupItem();

	void UnloadPickupItem();

	UFUNCTION(BlueprintImplementableEvent, Category="ItemPickup")
	void MarkPickupForGarbage();

	virtual void OnConstruction(const FTransform& Transform) override;

	void AddItemToInventory(AActor* ActorToAddItem);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="ItemInteraction")
	void OnPickupStartFocus();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="ItemInteraction")
	void OnPickupEndFocus();

	virtual void OnInteract_Implementation(AActor* InstigatorActor) override;

	virtual void OnStartFocus_Implementation() override;

	virtual void OnEndFocus_Implementation() override;
};
